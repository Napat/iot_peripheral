import sys, getopt
import ampy.files as files
import ampy.pyboard as pyboard

_pyboard = None
_port = None
_cmd = None
_src = None
_ready = False

def main(argv):
	global _pyboard, _port, _cmd, _src
	opts, args = getopt.getopt(argv, "p:c:f:")
	for opt, arg in opts:
		if opt == '-p' :
			_port = arg
		elif opt == '-c' :
			_cmd = arg
		elif opt == "-f" :
			_src = arg
	exec_file()

def exec_file():
	global _pyboard, _port, _cmd, _src
	result = None
	if _port is not None:
		_pyboard = pyboard.Pyboard(_port)
		_file_board = files.Files(_pyboard)
		if _cmd == 'run'   :
			if _src is not None :
				result =  _file_board.run(_src)
		elif _cmd == 'ls':
			result = _file_board.ls()
		elif _cmd == 'get':
			if _src is not None :
				result = _file_board.get(_src)
		elif _cmd == 'put':
			if _src is not None:
				result = _file_board.put(_src)
	_pyboard = None
	_port = None
	_cmd = None
	_src = None
	_file_board = None

	print(result)


main(sys.argv[1:])
			
	

