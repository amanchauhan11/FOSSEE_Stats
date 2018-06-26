var els = document.getElementsByTagName('path');
var str = '<ore>&lt;?php <br><br>function state_array() {<br>   &nbsp;&nbsp;&nbsp;&nbsp;$states = array(';
var e = document.querySelector('svg g g');
for(var i=0;i<els.length;i++){
    str += '<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"'+els[i].getAttribute('title')+'" => "'+els[i].getAttribute('d')+'" ,<br>';
}
str += '<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"matrix" => "'+e.getAttribute('transform')+'"</br>'
document.write(str+"&nbsp;&nbsp;&nbsp;&nbsp;);<br>&nbsp;&nbsp;&nbsp;&nbsp;return $states; <br>}<br><br>?&gt;");
