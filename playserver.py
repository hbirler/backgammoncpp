from flask import Flask, render_template, request
import subprocess
app = Flask(__name__)

def run_play(params):
	print "Running play"
	proc = subprocess.Popen(['bin/tavla', 'play']+params, stdout=subprocess.PIPE)
	tmp = proc.stdout.read()
	#print tmp
	return tmp

@app.route("/")
def hello():
	return render_template('index.htm')

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
	app.run(host="0.0.0.0",port=8888,debug=True,threaded=True)




