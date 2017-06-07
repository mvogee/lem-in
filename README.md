# lem-in
Graph path finding program.

<b>Getting Started</b><br>
<ul>
<li>Run Make to compile the lem-in executable.</li>
<li>lem-in will read input from the stdin in the form:</li><br>
  <ul>
    num_ants<br>
    nodes<br>
    node_links<br>
   </ul><br>
   <li>Rooms are defined by: name x_coord, y_coord</li>
   <li>Links are defined by: name1-name2</li>
   <li>Comments in the map definition start with #</li>
   <li>Commands in the map definition start with ##</li>
   <li>Valid commands are:</li><br>
    <ul>
    ##start (defines the starting node as the next node input)<br>
    ##end (defines the end node as the next node input)<br>
    </ul><br>
   <li>Use cntrl+D to stop reading from stdin</li>
   <li>It is best to use a text file containing the graph definition<br></li></ul>
<b>Output is in the form:</b>
<ul>
Lx-y Lz-w Lr-o ...<br>
Where x, z, and r, represent the ant number<br>
and y, w, and o represent the room name that they are moving to.</ul>

<b>Example graph definition</b>
<ul>
#Number of ants<br>
23<br>
#room definitions<br>
##start<br>
1 0 0<br>
2 0 0<br>
3 0 0<br>
4 0 0<br>
5 0 0<br>
6 0 0<br>
7 0 0<br>
##end<br>
0 0 0<br>
#room connections<br>
0-4<br>
0-6<br>
1-3<br>
4-3<br>
5-2<br>
3-5<br>
4-2<br>
2-1<br>
7-6<br>
7-2<br>
7-4<br>
6-5<br>
</ul>

