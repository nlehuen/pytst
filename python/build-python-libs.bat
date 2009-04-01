rem See http://www.redmountainsw.com/wordpress/archives/building-python-extensions-with-activepython-25-and-visual-studio-2005
for %%p in (23 24 25 26) do (
    pexports c:\\windows\\system32\\python%%p.dll > python%%p.def
    dlltool --dllname python%%p.dll --def python%%p.def --output-lib libpython%%p.a
    del python%%p.def
    move libpython%%p.a c:\python%%p\libs
)
