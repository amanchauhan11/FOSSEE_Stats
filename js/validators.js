(function ($) {
  Drupal.behaviors.fossee_stats = {
    attach: function (context, settings) {

      if (typeof Drupal.settings.fossee_stats.numvidlink !== 'undefined')
      {
      	var numvidlink = Drupal.settings.fossee_stats.numvidlink;
    		for(let i = 0; i < numvidlink; i++)
    		{
          let videoid = "#videolink_"+i.toString();
          $(videoid).change(
      	 	function(){
      	 				let link = $(this).val();
      	 				if( link.indexOf("http://") && link.indexOf("https://") && link.length)
      	 					{ $("#validate_url_"+i.toString()).css("visibility", "visible"); $('#edit-submit').prop('disabled', true);}
      	 				else
      	 					{ $("#validate_url_"+i.toString()).css("visibility", "hidden");  }
      	 			   }
     	    );

          let link = $(videoid).val();
          if( link.indexOf("http://") && link.indexOf("https://") && link.length)
            { $("#validate_url_"+i.toString()).css("visibility", "visible"); $('#edit-submit').prop('disabled', true);}
          else
            { $("#validate_url_"+i.toString()).css("visibility", "hidden");  }
    		}
      }

       $("#edit-event-link").change(
       		function(){
       					var link = $(this).val();
       					if( link.indexOf("http://") && link.indexOf("https://") && link.length)
       						{$("#validate_url").css("visibility", "visible");  $('#edit-submit').prop('disabled', true);}
       					else
                  { $("#validate_url").css("visibility", "hidden"); }
       				}
       );

       $("input[name='end_date[date]']").change(
       		function() {
       					if( $(this).val() < $("input[name='start_date[date]']").val())
       						{ $("#validate_date").css("visibility","visible"); $('#edit-submit').prop('disabled', true);}
       					else
                { $("#validate_date").css("visibility","hidden"); }
       				 }
      	);

       $("input[name='start_date[date]']").change(
          function() {
                if( $("input[name='end_date[date]']").val()!="" && $(this).val() > $("input[name='end_date[date]']").val())
                 { $("#validate_date").css("visibility","visible");  $('#edit-submit').prop('disabled', true);}
                else
                  { $("#validate_date").css("visibility","hidden");}
               }
        );

      /* $("input[name='start_date[time]']").change(
       		function() {
       			if($("input[name='end_date[date]']").val()==$("input[name='start_date[date]']").val())
       				if($(this).val()>$("input[name='end_date[time]']"))
       					{ $("#validate_time").css("visibility","visible"); $('#edit-submit').prop('disabled', true);}
       				else
       					{ $("#validate_time").css("visibility","hidden"); }
       		}

       	);

       $("input[name='end_date[time]']").change(
       		function() {
       			if($("input[name='end_date[date]']").val()==$("input[name='start_date[date]']").val())
       				if($(this).val()<$("input[name='start_date[time]']"))
       					{ $("#validate_time").css("visibility","visible");  $('#edit-submit').prop('disabled', true);}
       				else
       					{ $("#validate_time").css("visibility","hidden");}
       		}
       	);*/

      if(typeof Drupal.settings.fossee_stats.sortby !== undefined)
       	{ $("input[name='"+Drupal.settings.fossee_stats.sortby+"']").css("background", "lightgray"); }

    }
  };

}(jQuery));


function deletePrompt(id){
	if(prompt("Are you sure?")) window.location = "events/delete/"+ id;
}
