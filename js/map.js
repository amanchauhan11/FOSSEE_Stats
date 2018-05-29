

function hello(state){
  jQuery.ajax({
    type: 'POST',
    url: 'state-details',
    data: '{  "type" : "'+jQuery('#edit-foss-type').val()+'", "state" : "'+state+'"}',
    processData:false,
    contentType: "application/json",
    success:function(r){
      var data = JSON.parse(r);
      jQuery('body').html(jQuery('body').html() + '<div id="poped" onclick="close_popup()"><div id="popup"><div class="head"><span id="closer" onclick="close_popup()">&times;</span></div><h1>'+state+'</h1><h3>Workshop - '+data.Workshop+'</h3><h3>Conference - '+data.Conference+'</h3><h3>Lab Migration - '+data.lab_migration+'</h3><h3>TextBook Companion - '+data.pbc+'</h3><h3>DWSIM Flowsheet - '+data.Flowsheet+'</h3><h3>eSim Ciruit Simulation - '+data.circuit_simulation+'</h3></div></div>');
      //jQuery('#load_map svg').css('margin-top',-680);
      //jQuery('svg').css('opacity',0.5);

    },error:function(r){
      alert('not working!');
    }
  });
}

function close_popup() {
  //jQuery('svg').css('opacity',1);
  jQuery('body #poped').remove();
}
