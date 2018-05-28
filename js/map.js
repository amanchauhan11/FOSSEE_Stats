jQuery(document).ready(function(){
  /*
  jQuery('.state').click(function(){
    alert('asd');
    jQuery.ajax({
      // Method of Ajax Request
      method: 'GET',
      url: 'adding',
      // Data teken fron the submition form.
      data:{
        college_name: jQuery('#edit-college-name').val(),
        university_name: jQuery('#edit-university-name').val(),
        location: jQuery('#edit-location').val(),
        latitude: jQuery('#edit-latitude').val(),
        longitude: jQuery('#edit-longitude').val(),
        field_of_study: jQuery('#edit-field-of-study').val(),
        level_of_education: jQuery('#edit-level-of-education').val(),
        // Token to make the request secured
        token: mytoken
      },
      success:function(data){
        // If the data inserted successfully, a status will be displayed with the following HTML content
        jQuery('<div id="messages"><div class="section clearfix"><div class="messages status"><h2 class="element-invisible">Status message</h2>'+data+'</div></div></div>').insertAfter('#header');
      },
      error:function(){
        // If the data doesn't inserted successfully, a alert message of HTML content will be displayed
        jQuery('<div id="messages"><div class="section clearfix"><div class="messages error"><h2 class="element-invisible">Error message</h2>Every Field is need to fill up!</div></div></div>').insertAfter('#header');
      }
    });
  });*/
});

function hello(state){
  jQuery.ajax({
    type: 'POST',
    url: 'state-details',
    data: '{  "type" : "'+jQuery('#edit-foss-type').val()+'", "state" : "'+state+'"}',
    processData:false,
    contentType: "application/json",
    success:function(r){
      var data = JSON.parse(r);
      // If the data inserted successfully, a status will be displayed with the following HTML content
      jQuery('#load_map svg').hide();
      jQuery('#load_map').html(jQuery('#load_map').html() + '<div id="poped"><div id="popup"><div class="head"><span id="closer" onclick="close_popup()">close</span></div><h1>'+state+'</h1><h3>Workshop - '+data.Workshop+'</h3><h3>Conference - '+data.Conference+'</h3><h3>Lab Migration - '+data.lab_migration+'</h3><h3>TextBook Companion(Pending) - '+data.pbc+'</h3><h3>TextBook Companion(Completed) - '+data.tbc+'</h3><h3>Self Workshop - '+data.self_workshop+'</h3><a onclick="close_popup()">Back to Map</a></div></div>');

    },error:function(r){
      alert('not working!');
    }
  });
}

function close_popup() {
  jQuery('#load_map svg').show();
  jQuery('#load_map #poped').remove();
}
