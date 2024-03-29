# QT Table Row Age Fading Example
This project shows an efficient way to highlight new rows in a QT Table with a temporal colour fade.

# Design
A QT Timer triggers a callback that iterates through the rows in time order, stopping when it reaches one older than the specified threshold.
Once it reaches this row, because the data is sorted, all rows afterwards are also older than the threshold.

For each row newer than the threshold, the "update rows" signal is emitted.

When redrawing the row, a colour fading from red to white is selected based on its age.

When the table is empty or the first row is older than the threshold, the timer will stop. If it is stopped and a new row is added,
then the timer is started again. This ensures that it is not running unnecessarily.
