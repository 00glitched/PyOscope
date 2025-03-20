PATH=pwd
virtualenv -p python3 $PATH/.pyoscope
source $PATH/.pyoscopevenv/bin/activate 

pip install -r deplist.md
