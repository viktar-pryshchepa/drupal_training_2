;(function($){
       Drupal.CTools.Modal.show('my-modal-style');
       var user_create_date = Drupal.settings.user_create_date;
       var days_to_new_year = Drupal.settings.days_to_new_year;
       var html = '';
       html += '<div>User created on: ';
       html += user_create_date;
       html +='</div>';
       html += '<div>Days before new year: ';
       html += days_to_new_year;
       html +='</div>';
       Drupal.behaviors.coolsAlert = {
            attach: function(context) {
                console.log('hello');
                jQuery("#modal-content")[0].innerHTML = html;
            }
       };
   })(jQuery)
