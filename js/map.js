function hello(state){
  jQuery.ajax({
    type: 'POST',
    url: 'state-details',
    data: '{  "type" : "'+jQuery('#edit-foss-type').val()+'", "state" : "'+state+'"}',
    processData:false,
    contentType: "application/json",
    success:function(r){
      var data = JSON.parse(r);
      var out = '';
      var status = 0;
      if(data.Workshop != 0){
        out += '<h3>Workshop - '+data.Workshop+'</h3>';
        status = 1;
      }
      if(data.Conference != 0){
        out += '<h3>Conference - '+data.Conference+'</h3>';
        status = 1;
      }
      if(data.lab_migration != 0){
        out += '<h3>Lab Migration - '+data.lab_migration+'</h3>';
        status = 1;
      }
      if(data.pbc != 0){
        out += '<h3>TextBook Companion - '+data.pbc+'</h3>';
        status = 1;
      }
      if (data.Flowsheet != 0) {
        out += '<h3>DWSIM Flowsheet - '+data.Flowsheet+'</h3>';
        status = 1;
      }
      if (data.circuit_simulation != 0) {
        out += '<h3>eSim Ciruit Simulation - '+data.circuit_simulation+'</h3>';
        status = 1;
      }
      /*if (data.selfworkshop != 0) {
        out += '<h3>Self Workshop - '+data.selfworkshop+'</h3>';
        status = 1;
      }*/
      if (status == 0) {
        out = '<h3>There is no data available</h3>';
      }
      jQuery('body').html(jQuery('body').html() + '<div id="poped" onclick="close_popup('+jQuery('#edit-foss-type').val()+')"><div id="popup"><div class="head"><span id="closer" onclick="close_popup('+jQuery('#edit-foss-type').val()+')">&times;</span><h1>'+state+'</h1></div><div class="body">'+out+'</div></div></div>');
    },error:function(r){
      alert('not working!');
    }
  });
}

function close_popup(state) {
  //jQuery('svg').css('opacity',1);
  jQuery('body #poped').remove();
  jQuery('#edit-foss-type').val(state);
}

function map(){
  jQuery.ajax({
    type: 'POST',
    url: 'map-stats',
    data: '{  "type" : "'+jQuery('#edit-foss-type').val()+'"}',
    processData:false,
    contentType: "application/json",
    success:function(r){
      jQuery('#load_map').html(r);
    },error:function(r){
      alert('not working!');
    }
  });
}
