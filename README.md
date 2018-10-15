Retreat form and management tools for acinstlouis.org.

8/16/13:
Some Details about the Retreat Form Module

The retreat is for a weekend with lodging.  There are 3 lodging options plus a commuter option.
The 3 lodging options are: private room and bath, private room with a shared bath (one other person) and shared room with private bath.

If the shared room option is selected on the registration form, I have a drop down selection box come up with all the names of people
that have registered for a shared room but don't have a roommate.  That way, they are matched up.  If there is no one else registered
or the person they want to room with isn't listed, they can select that their roommate hasn't registered yet.

The retreat center will assign us different rooms every year.  The manage rooms form is available to be able to select which rooms we have.
It can also be used to reserve rooms, like if the retreat center asks we fill the second floor first.  Also, because the demand for
private rooms with private baths is always higher than the amount available, the manage rooms form lets us change a room from 2 beds to 1,
making it count as a private room.

The configuration of the rooms is then used in the total available count that is displayed after each room option on the registration form.
This was previously done with constant defines.  This way one of the other council members can change the rooms as needed.

The rest of the configuration is handled with configuration form, which was recently expanded because this year there will be a second
retreat (first time in 7 years) that has different configuration requirements.

One configuration feature is deadline dates and times.  The dates are used to change the messages at the top of the form as appropriate,
or remove the room options when the lodging deadline has passed.  That way I don't have to be available to change the form at say, midnight.

There are also several email tools such as sending an update to all registrants, sending an email to a single registrant (select from a drop
down of all registrants, multiple selections allowed) and a log of the individual emails.

Planned updates:  Add room assignment to the manage rooms form plus fix the javascript.