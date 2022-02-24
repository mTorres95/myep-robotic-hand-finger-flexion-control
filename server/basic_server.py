from http.server import BaseHTTPRequestHandler, HTTPServer
import cgi
import sys
import socket

from transformHtmlFile import add_html_file

html_file_name = "FlexionOfFingers.html"
global finger1content, finger2content, finger3content, finger4content,finger5content

class Socket:
    def iniciar(self, puerto):
        ipLocal = socket.gethostbyname(socket.gethostname())
        print ("Esperando conexiones... [IP local: ",ipLocal,"]")
        addr = socket.getaddrinfo(ipLocal, puerto)[0][-1]
        s = socket.socket()
        s.bind(addr)
        s.listen(1)
        cl, addr = s.accept()
        print('Cliente conectado desde', addr)
        print('Escuchando en', addr)
        return cl

def MakeHandler(cl):

    class webserverHandler(BaseHTTPRequestHandler):
        """docstring for webserverHandler"""

        def do_GET(self):
            try:
                self.send_response(200)
                self.send_header('Content-Type', 'text/html')
                self.end_headers()
                
                html_file = add_html_file(html_file_name, ["0","0","0","0","0"])
                self.wfile.write(html_file.encode())
                return

            except IOError:
                self.send_error(404, "File not found %s" % self.path)

        def do_POST(self):
            try:
                self.send_response(301)
                self.send_header('Content-Type', 'text/html')
                self.end_headers()
                ctype, pdict = cgi.parse_header(self.headers.get('Content-Type'))
                pdict['boundary'] = bytes(pdict['boundary'], "utf-8")
                if ctype == 'multipart/form-data':
                    fields = cgi.parse_multipart(self.rfile, pdict)
                    finger1content = fields.get('finger1')
                    finger2content = fields.get('finger2')
                    finger3content = fields.get('finger3')
                    finger4content = fields.get('finger4')
                    finger5content = fields.get('finger5')
                
                html_arguments = [finger1content[0], finger2content[0], finger3content[0], finger4content[0], finger5content[0]]
                
                cl.sendall(bytes(":A"+finger1content[0]+
                                 "B" +finger2content[0]+
                                 "C" +finger3content[0]+
                                 "D" +finger4content[0]+
                                 "E" +finger5content[0]+
                                 "\r\n", "utf-8"))
                #cl.sendall(bytes("F2"+finger2content[0]+"\n", "utf-8"))
                #cl.sendall(bytes("F3"+finger3content[0]+"\n", "utf-8"))
                #cl.sendall(bytes("F4"+finger4content[0]+"\n", "utf-8"))
                #cl.sendall(bytes("F5"+finger5content[0]+"\n", "utf-8"))

                html_file = add_html_file(html_file_name, html_arguments)
                self.wfile.write(html_file.encode())
            except:
                self.send_error(404, "{}".format(sys.exc_info()[0]))
            print(sys.exc_info())

    return webserverHandler

def main():
    try:
        print("Inicio del programa")
        # to open the html in a browser and get the values of the sliders
        port = 80
        server_address = ('0.0.0.0', port)

        
        # to send the information to the ESP8266 client
        socket = Socket()
        cl = socket.iniciar(80)

        Handler = MakeHandler(cl)
        server = HTTPServer(server_address, Handler)
        print("Web server running on port %s" % port)
        server.serve_forever()

    except KeyboardInterrupt:
        print(" ^C entered stopping web server...")
        server.socket.close()

if __name__ == '__main__':
    main()