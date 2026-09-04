import os
from wsgiref.simple_server import make_server

CONTENT_TYPE = {
	'.html': 'text/html; charset=utf-8', '.txt': 'text/plain; charset=utf-8', '.json': 'application/json',
	'.js': 'text/javascript', '.css':'text/css', '.ico': 'image/vnd.microsoft.icon', '.jpg': 'image/jpeg',
	'.png': 'image/png', '.gif': 'image/gif', '.webp': 'image/webp'
};

def application(environ, start_response):
	content_type = 'text/plain; charset=utf-8'
	output_text = ''
	output_data = None
	path_info = environ['PATH_INFO']

	if 'program-a' in path_info:
		output_text = 'called wsgi program-a'

	elif 'program-b' in path_info:
		output_text = 'called wsgi program-b'

	elif '.' in path_info:
		full_path = '.' + ( path_info + 'index.html' if path_info.endswith('/') else path_info)
		file_name, file_ext = os.path.splitext(full_path)
		if file_ext in CONTENT_TYPE:
			if os.path.isfile(full_path):
				with open(full_path, mode='br') as f:
					output_data = f.read()
					content_type = CONTENT_TYPE[file_ext]
			else:
				output_text = 'file path not found'
		else:
			output_text = 'not supported ext type'
	else:
		output_text = 'not supported file path'

	headers = [('Content-type', content_type)]
	start_response('200 OK', headers)

	if output_data != None:
		return [bytes(output_data)]

	return [bytes(output_text.encode('utf-8'))]

with make_server('', 8000, application) as httpd:
	print('make_server port 8000...')
	httpd.serve_forever()
