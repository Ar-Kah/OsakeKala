#
# Web based GUI for UCE chess engine
#

# packages
from flask import Flask
from flask import render_template
from flask import request
import chess
import chess.engine

# create web app instance
app = Flask(__name__)

#define root(index) route
@app.route('/')
def root():
    return render_template('UCE.html')

# make move API
@app.route('/make_move', methods=['POST'])
def make_move():
    # extract FEN string from HTTP POST body
    fen = request.form.get('fen')

    board = chess.Board(fen)
    print(board)
    return {'fen': 'make move'}

# main driver
if __name__ == '__main__':
    # start HTTP server
    app.run(debug=True, threaded=True)
