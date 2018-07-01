#! /bin/bash
# If already admin, just run the command in-line.
# This works on my Win10 machine; dunno about others.
if id -G | grep -q ' 544 '; then
   "$@"
   exit $?
fi

# cygstart/runas doesn't handle arguments with spaces correctly so create
# a script that will do so properly.
tmpfile=$(mktemp /tmp/sudo.XXXXXX)
echo "#! /bin/bash" >>$tmpfile
echo "export PATH=\"$PATH\"" >>$tmpfile
echo "$1 \\" >>$tmpfile
shift
for arg in "$@"; do
  qarg=`echo "$arg" | sed -e "s/'/'\\\\\''/g"`
  echo "  '$qarg' \\" >>$tmpfile
done
echo >>$tmpfile

# cygstart opens a new window which vanishes as soon as the command is complete.
# Give the user a chance to see the output.
echo "echo -ne '\n$0: press <enter> to close window... '" >>$tmpfile
echo "read enter" >>$tmpfile

# Clean up after ourselves.
echo "rm -f $tmpfile" >>$tmpfile

# Do it as Administrator.
cygstart --action=runas /bin/bash $tmpfile
