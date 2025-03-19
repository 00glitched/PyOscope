PATH=pwd
virtualenv -p python3 $PATH/.pyvenv
source $PATH/.pyvenv/bin/activate 

pip install -r deplist.md
