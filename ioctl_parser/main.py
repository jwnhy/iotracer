from dissect import cstruct
import sys

def process_struct(env, header, lineno):
    if header[lineno].startswith('typedef'):
        env['typedefs'].append(header[lineno])
    if not any([header[lineno].startswith(x) for x in ['union', 'struct']]):
        return lineno
    begin = lineno
    while header[lineno].strip() != '};':
        lineno += 1
    struct_def = ''.join(env['typedefs'] + header[begin:lineno+1])
    struct_def = struct_def.replace(' in;', ' _in;')
    #print(struct_def)

    parser = env['parser']
    parser.load(struct_def)
    return lineno

def process_define(env, header, lineno):
    if not header[lineno].startswith('#define'):
        return lineno

    line = header[lineno].strip()
    if line.endswith('\\'):
        line = line[:-1].strip()
        to_append = header[lineno+1].strip()
        line = ' '.join([line, to_append])
        lineno += 1
    if all([x not in line for x in ['_IOW(', '_IOR(', '_IOWR(', '_IO(']]):
        return lineno
    elems = [x.strip() for x in line.split(' ', 2)]
    
    cmd = elems[2]
    cmd_typ = cmd[:cmd.find('(')]
    cmd_params = cmd[cmd.find('(')+1: cmd.find(')')]
    if cmd_typ == '_IO':
        struct = None
    else:
        struct = cmd_params.split(',')[2].strip()
    env['cmds'][elems[1]] = {
            'name': elems[1],
            'cmd': cmd, 
            'typ': cmd_typ,
            'params': cmd_params,
            'struct': struct
    }
    return lineno

def dispatcher_ret_sizes(name, cmd, **kwargs):
    if cmd['typ'] in ['_IO']:
        return
    struct = cmd['struct']
    prefix = struct.split(' ')[0]
    print(f'      return sizeof({struct});')

def dispatcher_arg_sizes(name, cmd, **kwargs):
    if cmd['typ'] in ['_IO']:
        return
    struct = cmd['struct']
    print(f'      return sizeof({struct});')

def dispatcher_cmd_names(name, cmd, **kwargs):
    name = cmd['name']
    print(f'      return (uint64_t) "{name}";')

def dispatcher_printers(name, cmd, **kwargs):
    direction = kwargs['direction']
    if cmd['typ'] == '_IO':
        return
    struct = cmd['struct']
    is_union = struct.split(' ')[0] == 'union';
    name = struct.split(' ')[1]
    if is_union:
        print(f'      printer_{name}_{direction}(({struct} *)arg);')
    else:
        print(f'      printer_{name}(({struct} *)arg);')

def output_dispatcher(env, name, file, functor, **kwargs):
    cmds = env['cmds']
    saved_out = sys.stdout
    sys.stdout = file
    print(f'static inline uint64_t {name}(uint64_t cmd, uint64_t arg) {{')
    print(f'  switch(cmd) {{')
    for name, cmd in cmds.items():
        print(f'    case {name}:')
        functor(name, cmd, **kwargs)
        print(f'      break;')
    print(f'  }}')
    print(f' return 0;')
    print(f'}}')
    sys.stdout = saved_out

def printer_naive(field, indent):
    typ, name = field.type, field.name
    if isinstance(typ, cstruct.types.Structure) or isinstance(typ, cstruct.types.Union):
        print(' '*indent + name)
        for child_field in typ.fields:
            printer_naive(child_field, indent+2)
    elif isinstance(typ, cstruct.types.BaseType):
        print(f"{indent*' '}{name}: {typ}")

def helper_printer(typ, name, io=''):
    if isinstance(typ, cstruct.types.Structure):
        print(f'  printer_{typ.name}(arg{io}{name});')
    elif isinstance(typ, cstruct.types.Array):
        pass
    elif isinstance(typ, cstruct.types.BaseType):
        sanitized_name = name.replace('->', '').replace('.', '')
        if typ.name in ['uint8', 'uint16', 'uint32']:
            print(f'  printf("  {sanitized_name}: 0x%x\\n", arg{io}{name});')
        else:
            print(f'  printf("  {sanitized_name}: 0x%lx\\n", arg{io}{name});')

def printer_structure(field, indent):
    typ, name = field.type, field.name
    if isinstance(typ, cstruct.types.Union):
        for direction in ['_in', 'out']:
            esp_dir = direction.replace('_', '')
            print(f'static inline int printer_{name}_{esp_dir}(union {typ.name}* arg) {{')
            io = [io for io in typ.fields if io.name == direction][0]
            for f in io.type.fields:
                childtyp, childname = f.type, f.name
                helper_printer(childtyp, f'.{childname}', f'->{esp_dir}')
            print(f'  return 0;')
            print(f'}}')
    elif isinstance(typ, cstruct.types.Structure):
        print(f'static inline int printer_{name}(struct {typ.name}* arg) {{')
        for f in typ.fields:
            childtyp, childname = f.type, f.name
            helper_printer(childtyp, f'->{childname}')
        print(f'  return 0;')
        print(f'}}')
        
def output_printer(env, file, functor=printer_naive):
    processed = set()
    parser = env['parser']
    saved_out = sys.stdout
    sys.stdout = file
    for name, cmd in env['cmds'].items():
        if cmd['typ'] == '_IO':
            continue
        struct_name = cmd['struct'].split(' ')[1]
        if struct_name in processed:
            continue
        processed.add(struct_name)
        struct = parser.resolve(struct_name)
        top_field = cstruct.Field(struct_name, struct)
        functor(top_field, 0)
    sys.stdout = saved_out

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: ./main.py <ioctl_header>')
        exit(-1)

    env = {
        'cmds': dict(),
        'typedefs': list(),
        'parser': cstruct.cstruct()
    }
    
    header = open(sys.argv[1], 'r').readlines()
    lineno = 0
    while lineno < len(header):
        lineno = process_struct(env, header, lineno)
        lineno = process_define(env, header, lineno)
        lineno += 1

    # output 'gpu_bpf.h'
    with open('../gpu_bpf.h', 'w') as f:
        print('#include "gpu_ioctl.h"', file=f)
        output_dispatcher(env, 'sizeofarg', f, dispatcher_arg_sizes)
        output_dispatcher(env, 'sizeofret', f, dispatcher_ret_sizes)
    with open('../gpu_user.h', 'w') as f:
        print('#include "gpu_ioctl.h"', file=f)
        print('#include <stdio.h>', file=f)
        output_printer(env, f, printer_structure)
        output_dispatcher(env, 'cmdname', f, dispatcher_cmd_names)
        output_dispatcher(env, 'printerofarg', f, functor=dispatcher_printers, direction='in')
        output_dispatcher(env, 'printerofret', f, functor=dispatcher_printers, direction='out')
