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
    print(struct_def)

    parser = env['parser']
    parser.load(struct_def, compiled=False)
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
    #print(cmd_params)
    env['cmds'][elems[1]] = {
            'cmd': cmd, 
            'typ': cmd_typ,
            'params': cmd_params,
            'struct': struct
    }
    return lineno
        

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
    for k, v in env['cmds'].items():
        pass
        #print(k, v)
