
var states = [];
var x = document.getElementsByTagName("path");
var i;
for (i = 0; i < x.length; i++) {
    states[x[i].getAttribute("title")] = x[i].getAttribute("d");
}
