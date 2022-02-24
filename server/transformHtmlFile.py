import os

def add_html_file(file, arguments) :
    script_path = (os.path.abspath(__file__)).split(os.sep)[0:-1]
    file_path = os.path.relpath(file)
    path = "/".join(script_path) + "/" + file_path

    f = open(path, 'r')
    lines = f.readlines()
    f.close()


    arg_nb = 0  # to count the number of arguments the html needs

    html = ''
    for x in lines:
        if '%s' in x:
            html = html + x.replace('%s',arguments[arg_nb]) + '\n'
            arg_nb += 1
        elif not (x=="''" or x=="'"):
            html = html + x + '\n'

    return html