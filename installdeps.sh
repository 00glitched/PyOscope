PATH=pwd
virtualenv -p python3 $PATH/.pyoscopevenv
source $PATH/.pyoscopevenv/bin/activate 

pip install -r deplist.md
