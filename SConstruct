Execute(Delete("dist"))
Execute(Mkdir(".config"))
Execute(Mkdir(".data"))
VariantDir('.build', 'src')
SConscript('src/SConscript.py', variant_dir='.build')
