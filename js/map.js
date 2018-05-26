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
    method: 'GET',
    url: 'state-details',
    data:{
      type: jQuery('edit-foss-type').val(),
      state: state
    },
    success:function(data){
      //alert(state);
      // If the data inserted successfully, a status will be displayed with the following HTML content
      jQuery('body').html() + '<div id="poped" class="cover-pop"><h2>'+state+'</h2></div>';
    }
  });
}
