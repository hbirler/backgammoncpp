from flask import Flask, render_template, request,send_from_directory
import subprocess
app = Flask(__name__)



from datetime import timedelta
from flask import make_response, request, current_app
from functools import update_wrapper


def crossdomain(origin=None, methods=None, headers=None,
				max_age=21600, attach_to_all=True,
				automatic_options=True):
	if methods is not None:
		methods = ', '.join(sorted(x.upper() for x in methods))
	if headers is not None and not isinstance(headers, basestring):
		headers = ', '.join(x.upper() for x in headers)
	if not isinstance(origin, basestring):
		origin = ', '.join(origin)
	if isinstance(max_age, timedelta):
		max_age = max_age.total_seconds()

	def get_methods():
		if methods is not None:
			return methods

		options_resp = current_app.make_default_options_response()
		return options_resp.headers['allow']

	def decorator(f):
		def wrapped_function(*args, **kwargs):
			if automatic_options and request.method == 'OPTIONS':
				resp = current_app.make_default_options_response()
			else:
				resp = make_response(f(*args, **kwargs))
			if not attach_to_all and request.method != 'OPTIONS':
				return resp

			h = resp.headers

			h['Access-Control-Allow-Origin'] = origin
			h['Access-Control-Allow-Methods'] = get_methods()
			h['Access-Control-Max-Age'] = str(max_age)
			if headers is not None:
				h['Access-Control-Allow-Headers'] = headers
			return resp

		f.provide_automatic_options = False
		return update_wrapper(wrapped_function, f)
	return decorator




def run_play(params):
	print "Running play"
	print "asdasdf"
	for i in xrange(4):
		try:
			proc = subprocess.Popen(['bin/tavla', 'play']+params, stdout=subprocess.PIPE)
			tmp = proc.stdout.read()
			break
		except:
			continue
	#print tmp
	return tmp

@app.route("/")
def hello():
	return render_template('index.htm')

@app.route("/test")
def testview():
	return send_from_directory('output', 'testout.txt')

@app.route("/logdata")
def logdataview():
	return send_from_directory('output', 'testlog.jsonl', mimetype='text/json')
	
@app.route("/log")
def logview():
	return render_template('tests.htm')
	
@app.route("/weights")
@crossdomain(origin='*')
def getweights():
	return send_from_directory('output', 'weights.bin', mimetype='application/octet-stream')

@app.route("/play")
def play():
	game = request.args.get('game')
	dice = request.args.get('dice')
	if game is None:
		res = run_play([])
	else:
		params = [game]
		if dice is not None:
			params = params + dice.split(',')
		res = run_play(params)
	return res
	
	
	


if __name__ == "__main__":
	app.run(host="0.0.0.0",port=5000,debug=True,threaded=True)




