#!/bin/csh

# Find the counts of all of the stuff
set user = "`grep -c stat=User email.log`"
set sent = "`grep -c stat=Sent email.log`"
set deferred = "`grep -c stat=Deferred email.log`"
set discarded = "`grep -c Discarded: email.log`"
set rejected = "`grep -c reject= email.log`"

# Print the counts to the screen
echo "User status messages: $user"
echo "Sent status messages: $sent"
echo "Deferred status messages: $deferred"
echo "Discarded messages: $discarded"
echo "Rejected messages: $rejected"
