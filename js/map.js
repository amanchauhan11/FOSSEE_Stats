
// To popup state data
function hello(state){
  var add = '';
  var sub = '';
  if (!jQuery('#edit-foss-type').val()) {
    sub += '0'
  }
  if(jQuery('#edit-foss-activities').val()){
    add += ', "activities" : "'+jQuery('#edit-foss-activities').val()+'"';
    sub += ','+jQuery('#edit-foss-activities').val();
  }else {
    sub += ',0';
  }
  if(jQuery('#edit-foss-status').val()){
    add += ', "status" : "'+jQuery('#edit-foss-status').val()+'"';
    sub += ','+jQuery('#edit-foss-status').val();
  }else {
    sub += ',0';
  }
  // Ajax request to get state data
  jQuery.ajax({
    type: 'POST',
    url: 'state-details',
    data: '{  "type" : "'+jQuery('#edit-foss-type').val()+'", "state" : "'+state+'" '+add+'}',
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
      if(data.lab_migration_completed != 0){
        out += '<h3>Lab Migration (Completed) - '+data.lab_migration_completed+'</h3>';
        status = 1;
      }
      if(data.lab_migration_pending != 0){
        out += '<h3>Lab Migration (Pending) - '+data.lab_migration_pending+'</h3>';
        status = 1;
      }
      if(data.PendingBookCount != 0){
        out += '<h3>TextBook Companion (Pending) - '+data.PendingBookCount+'</h3>';
        status = 1;
      }
      if(data.CompletedBookCount != 0){
        out += '<h3>TextBook Companion (Completed) - '+data.CompletedBookCount+'</h3>';
        status = 1;
      }
      if (data.Flowsheet_completed != 0) {
        out += '<h3>DWSIM Flowsheet (Completed)- '+data.Flowsheet_completed+'</h3>';
        status = 1;
      }
      if (data.Flowsheet_pending != 0) {
        out += '<h3>DWSIM Flowsheet (Pending)- '+data.Flowsheet_pending+'</h3>';
        status = 1;
      }
      if (data.circuit_simulation_completed != 0) {
        out += '<h3>eSim Ciruit Simulation (Completed)- '+data.circuit_simulation_completed+'</h3>';
        status = 1;
      }
      if (data.circuit_simulation_pending != 0) {
        out += '<h3>eSim Ciruit Simulation (Pending)- '+data.circuit_simulation_pending+'</h3>';
        status = 1;
      }
      /*if (data.selfworkshop != 0) {
        out += '<h3>Self Workshop - '+data.selfworkshop+'</h3>';
        status = 1;
      }*/
      if (status == 0) {
        out = '<h3>There is no data available</h3>';
      }
      jQuery('body').html(jQuery('body').html() + '<div id="poped" onclick="close_popup('+jQuery('#edit-foss-type').val()+sub+')"><div id="popup"><div class="head"><span id="closer" onclick="close_popup('+jQuery('#edit-foss-type').val()+sub+')">&times;</span><h1>'+state+'</h1></div><div class="body">'+out+'</div></div></div>');
    },error:function(r){
      alert('not working!');
    }
  });
}

// To close popup
function close_popup(type,activities,status) {
  jQuery('body #poped').remove();
  jQuery('#edit-foss-type').val(type);
  if (activities != 0) {
      jQuery('#edit-foss-activities').val(activities);
  }
  if (status != 0) {
      jQuery('#edit-foss-status').val(status);
  }
}

// To generate map according to activities and status
function map(){
  var add = '';
  if(jQuery('#edit-foss-activities').val()){
    add += ', "activities" : "'+jQuery('#edit-foss-activities').val()+'"';
  }
  if(jQuery('#edit-foss-status').val()){
    add += ', "status" : "'+jQuery('#edit-foss-status').val()+'"';
  }
  // Ajax request to generate map
  jQuery.ajax({
    type: 'POST',
    url: 'map-stats',
    data: '{ "type" : "'+jQuery('#edit-foss-type').val()+'"'+add+'}',
    processData:false,
    contentType: "application/json",
    success:function(r){
      jQuery('#load_map').html(r);
    },error:function(r){
      alert('not working!');
    }
  });
}

// To enable the activities dropdown
function check_activities() {
  jQuery.ajax({
    type: 'POST',
    url: 'dropdowns',
    data: '{ "Type" : "activities", "ID" : "'+jQuery('#edit-foss-type').val()+'"}',
    processData: false,
    contentType: "application/json",
    success:function(r){
      jQuery('#activities').html(r);
    },error:function(r){
      alert('not working!');
    }
  });
}

// To enable status dropdown
function check_status() {
  jQuery.ajax({
    type: 'POST',
    url: 'dropdowns',
    data: '{ "Type" : "status", "ID" : "'+jQuery('#edit-foss-activities').val()+'"}',
    processData: false,
    contentType: "application/json",
    success:function(r){
      jQuery('#status').html(r);
    },error:function(r) {
      alert('Not working!!!');
    }
  });
}
