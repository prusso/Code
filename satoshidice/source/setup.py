from distutils.core import setup
import py2exe, sys, os

if len(sys.argv) == 1: 
	sys.argv.append('py2exe')
	sys.argv.append('-q')
 
setup(console=['satoshidice.py'],
	data_files = ['msvcp90.dll','satoshidice.ini',],
	options=dict(py2exe=dict(
          excludes=["Tkconstants","Tkinter","tcl"],
          bundle_files=1,
		  ascii=1,
		  compressed=True,
		  unbuffered=True,
          optimize=2)),			
	zipfile = None
				)