all: p1.eps p2.eps

p1.eps: mleak_check.root mk_p1.py
	mk_p1.py

p2.eps: mleak_check.no_leak.root mk_p2.py
	mk_p2.py

mleak_check.root: mleak_chk.log proc.py
	proc.py $<

mleak_check.no_leak.root: mleak_chk.no_leak.log proc.py
	proc.py $<
