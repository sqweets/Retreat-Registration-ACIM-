<?php


/*
 * Config form for the retreat registration form.
 */


function retreatform_config_form($form, &$form_state) {
  
  $form['le_title'] = array(
    '#type' => 'item',
    '#title' => t('Retreat Form Configuration'),
  );

  $form['notice'] = array(
      '#markup' => t('<h2 style="text-align: left;">Change the "Year of Retreat" to the current year to start a new retreat registration.</br>If more than one retreat per year, add a 2 letter descriptive code to each additional retreat.</h2></br>'),
  );
  
  $form['retreat_year'] = array(
    '#type' => 'textfield',
    '#title' => t('Year of Retreat'),
    '#size' => 6,
    '#maxlength' => 6,
    '#required' => TRUE,
    '#description' => t('Enter the form 20##, or 20##CC'),
    '#default_value' => variable_get('retreat_year', '2013'),
  );
  

  // Setup options
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options Setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['options']['scholarship'] = array(
    '#type' => 'fieldset',
    '#title' => t('Scholarship Setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['options']['scholarship']['scholarship_option'] = array(
    '#title' => t('Check YES to enable the Ruth Hanna Scholarship'),
    '#type' => 'select',
    '#options' => array('No' => t('No'), 'Yes' => t('Yes')),
    '#required' => TRUE,
    '#default_value' => variable_get('scholarship_option', 'Yes'),
  );
  // Enable scholarship display
  $form['options']['scholarship']['display_scholarship_option'] = array(
    '#type' => 'select',
    '#options' => array('No' => t('No'), 'Yes' => t('Yes')),
    '#title' => t("Check YES to display the scholarship payment option on the registration form"),
    '#states' => array(
      'visible' => array(
        ':input[name="scholarship_option"]' => array('value' => 'Yes'),
      ),
    ),
//    '#required' => TRUE,
//    '#description' => t('Enter the time as 24hr clock (24 is midnight).  Only enter the hour value.'),
    '#default_value' => variable_get('display_scholarship_option', 'Yes'),
  );  

  $form['options']['eb_option'] = array(
    '#title' => t('Check YES to enable Early Bird setup'),
    '#type' => 'select',
    '#options' => array('No' => t('No'), 'Yes' => t('Yes')),
    '#required' => TRUE,
    '#default_value' => variable_get('eb_option', 'Yes'),
  );

  $form['options']['lodging_deadline_option'] = array(
    '#title' => t('Check YES to enable both Lodging and Commuter Deadline options'),
    '#type' => 'select',
    '#options' => array('No' => t('No'), 'Yes' => t('Yes')),
    '#required' => TRUE,
    '#description' => t('Check NO to enable only one deadline for all registrations'),
    '#default_value' => variable_get('lodging_deadline_option', 'Yes'),
  );

  $form['options']['saturday_halfday_option'] = array(
    '#title' => t('Check YES to add the Saturday Half Day Option to the registration'),
    '#type' => 'select',
    '#options' => array('No' => t('No'), 'Yes' => t('Yes')),
    '#required' => TRUE,
    '#default_value' => variable_get('saturday_halfday_option', 'Yes'),
  );

  $form['options']['saturday_commuter_option'] = array(
    '#title' => t('Check YES to add the Saturday Commuter Option to the registration'),
    '#type' => 'select',
    '#options' => array('No' => t('No'), 'Yes' => t('Yes')),
    '#required' => TRUE,
    '#default_value' => variable_get('saturday_commuter_option', 'Yes'),
  );

  // Setup email text
  $form['email_setup'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email Setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['email_setup']['retreat_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('The Subject of all Retreat Emails.'),
    '#size' => 75,
    '#maxlength' => 75,
    '#required' => TRUE,
    '#default_value' => variable_get('retreat_email_subject', '2013 St. Louis ACIM Retreat With Regina Dawn Akers and Scott Grace'),
  );

  $form['email_setup']['retreat_title'] = array(
    '#type' => 'textfield',
    '#title' => t('The Title of the Retreat.'),
    '#size' => 75,
    '#maxlength' => 75,
    '#required' => TRUE,
    '#default_value' => variable_get('retreat_title', 'Following Spirit without Hesitation'),
  );

  /* Retreat Coordinator info */
  $form['retreat_coord_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Retreat Coordinator Info (for emails)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['retreat_coord_info']['retreat_coordinator'] = array(
    '#type' => 'textfield',
    '#title' => t("Retreat Coordinator's Name"),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
    '#default_value' => variable_get('retreat_coordinator', 'Corinne Esneault'),
  );

  $form['retreat_coord_info']['retreat_coordinator_email'] = array(
    '#type' => 'textfield',
    '#title' => t("Retreat Coordinator's Email"),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
    '#default_value' => variable_get('retreat_coordinator_email', 'cesneault@charter.net'),
  );

  $form['retreat_coord_info']['retreat_coordinator_phone'] = array(
    '#type' => 'textfield',
    '#title' => t("Retreat Coordinator's Phone Number"),
    '#size' => 15,
    '#maxlength' => 15,
    '#required' => TRUE,
    '#description' => t('Enter only numbers. It will be formated for the emails'),
    '#default_value' => variable_get('retreat_coordinator_phone', '314-843-0954'),
  );
  
  $form['retreat_coord_info']['retreat_coordinator_address_line1'] = array(
    '#type' => 'textfield',
    '#title' => t("Retreat Coordinator's Address (Number and Street)"),
    '#size' => 40,
    '#maxlength' => 40,
    '#required' => TRUE,
    '#description' => t('Enter the first address line that is included in the form email sent to mail registrants'),
    '#default_value' => variable_get('retreat_coordinator_address_line1', '10885 Ridge Forest Drive'),
  );

  $form['retreat_coord_info']['retreat_coordinator_address_line2'] = array(
    '#type' => 'textfield',
    '#title' => t("Retreat Coordinator's Address (City, State, Zip)"),
    '#size' => 40,
    '#maxlength' => 40,
    '#required' => TRUE,
    '#description' => t('Enter the second address line that is included in the form email sent to mail registrants'),
    '#default_value' => variable_get('retreat_coordinator_address_line2', 'St. Louis, MO  63123'),
  );

  /* Retreat Deadlines */
  $form['retreat_deadlines'] = array(
    '#type' => 'fieldset',
    '#title' => t('Retreat Deadlines'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Date of Retreat
  $form['retreat_deadlines']['retreat_date'] = array(
    '#type' => 'textfield',
    '#title' => t("Date of Retreat"),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
    '#description' => t('Enter the the date like this: MM/DD.'),
    '#default_value' => variable_get('retreat_date', '07/19'),
  );
  
  // Early Bird deadline date
  $form['retreat_deadlines']['retreat_earlybird_deadline'] = array(
    '#type' => 'textfield',
    '#title' => t("Early Bird Deadline Date"),
    '#size' => 30,
    '#maxlength' => 30,
    '#states' => array(
      'visible' => array(
        ':input[name="eb_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#prefix' => '<div style="float: left; margin-right: 20px;">',
    '#suffix' => '</div>',
    '#description' => t('Enter the the date like this: MM/DD'),
    '#default_value' => variable_get('retreat_earlybird_deadline', '06/01'),
  );
  
  // Early Bird deadline time
  $form['retreat_deadlines']['retreat_earlybird_deadline_time'] = array(
    '#type' => 'textfield',
    '#title' => t("Early Bird Deadline Time"),
    '#size' => 2,
    '#maxlength' => 2,
    '#states' => array(
      'visible' => array(
        ':input[name="eb_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#description' => t('Enter the time as 24hr clock (24 is midnight).  Only enter the hour value.'),
    '#default_value' => variable_get('retreat_earlybird_deadline_time', '24'),
  );
  
  // Lodging deadline date
  $form['retreat_deadlines']['retreat_lodging_deadline'] = array(
    '#type' => 'textfield',
    '#title' => t("Lodging Deadline Date"),
    '#size' => 30,
    '#maxlength' => 30,
    '#states' => array(
      'visible' => array(
        ':input[name="lodging_deadline_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#prefix' => '<div style="float: left; margin-right: 20px;">',
    '#suffix' => '</div>',
    '#description' => t('Enter the the date like this: MM/DD'),
    '#default_value' => variable_get('retreat_lodging_deadline', '07/19'),
  );

  // Lodging deadline time
  $form['retreat_deadlines']['retreat_lodging_deadline_time'] = array(
    '#type' => 'textfield',
    '#title' => t("Lodging Deadline Time"),
    '#size' => 2,
    '#maxlength' => 2,
    '#states' => array(
      'visible' => array(
        ':input[name="lodging_deadline_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#description' => t('Enter the time as 24hr clock (24 is midnight).  Only enter the hour value.'),
    '#default_value' => variable_get('retreat_lodging_deadline_time', '24'),
  );

  // Commuter deadline date
  $form['retreat_deadlines']['retreat_commuter_deadline'] = array(
    '#type' => 'textfield',
    '#title' => t("Commuter Deadline Date"),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
    '#prefix' => '<div style="float: left; margin-right: 20px;">',
    '#suffix' => '</div>',
    '#description' => t('Enter the the date like this: MM/DD.!breakIf there is no Lodging Deadline option,!breakthis date is the final deadline for!breakall registrations.', array('!break' => '</br>')),
    '#default_value' => variable_get('retreat_commuter_deadline', '07/19'),
  );

  // Commuter deadline time
  $form['retreat_deadlines']['retreat_commuter_deadline_time'] = array(
    '#type' => 'textfield',
    '#title' => t("Commuter Deadline Time"),
    '#size' => 2,
    '#maxlength' => 2,
    '#required' => TRUE,
    '#description' => t('Enter the time as 24hr clock (24 is midnight).  Only enter the hour value.'),
    '#default_value' => variable_get('retreat_commuter_deadline_time', '24'),
  );

  // Setup messages
  $form['setup_messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Message(s) Setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['setup_messages']['retreat_closed_msg'] = array(
    '#type' => 'textarea',
    '#title' => t('Closed Message'),
    '#description' => t('Enter the message that appears after the registration is closed. This messaage will be displayed in place of the form. Include any additional information, etc. Can be left blank.'),
    '#default_value' => variable_get('retreat_closed_msg', ''),
  );

  // Setup costs
  $form['costs_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cost Values (only enter numbers)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['costs_info']['private_room_cost'] = array(
    '#type' => 'textfield',
    '#title' => t('Cost of a Private Room'),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#prefix' => '<div style="float: left; margin-right: 20px; width: 175px;">',
    '#suffix' => '</div>',
    '#default_value' => variable_get('private_room_cost', '325'),
  );

  $form['costs_info']['private_rm_earlybird_cost'] = array(
    '#type' => 'textfield',
    '#title' => t('Increase in Private Room Cost After Early Bird Deadline'),
    '#size' => 4,
    '#maxlength' => 4,
    '#states' => array(
      'visible' => array(
        ':input[name="eb_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#default_value' => variable_get('private_rm_earlybird_cost', '50'),
  );

  $form['costs_info']['shared_room_cost'] = array(
    '#type' => 'textfield',
    '#title' => t('Cost of a Shared Room'),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#prefix' => '<div style="float: left; margin-right: 20px; width: 175px;">',
    '#suffix' => '</div>',
    '#default_value' => variable_get('shared_room_cost', '275'),
  );

  $form['costs_info']['shared_rm_earlybird_cost'] = array(
    '#type' => 'textfield',
    '#title' => t('Increase in Shared Room Cost After Early Bird Deadline'),
    '#size' => 4,
    '#maxlength' => 4,
    '#states' => array(
      'visible' => array(
        ':input[name="eb_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#default_value' => variable_get('shared_rm_earlybird_cost', '50'),
  );

  $form['costs_info']['commuter_cost'] = array(
    '#type' => 'textfield',
    '#title' => t('Cost of a Full Commuter Registration'),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#prefix' => '<div style="float: left; margin-right: 20px; width: 175px;">',
    '#suffix' => '</div>',
    '#default_value' => variable_get('commuter_cost', '200'),
  );

  $form['costs_info']['commuter_earlybird_cost'] = array(
    '#type' => 'textfield',
    '#title' => t('Increase in Commuter Cost After Early Bird Deadline'),
    '#size' => 4,
    '#maxlength' => 4,
    '#states' => array(
      'visible' => array(
        ':input[name="eb_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#default_value' => variable_get('commuter_earlybird_cost', '25'),
  );

  $form['costs_info']['saturday_commuter_cost'] = array(
    '#type' => 'textfield',
    '#size' => 3,
    '#maxlength' => 3,
    '#title' => t('Cost of Saturday Commuter Registration'),
    '#states' => array(
      'visible' => array(
        ':input[name="saturday_commuter_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#default_value' => variable_get('saturday_commuter_cost', '200'),
  );
  $form['costs_info']['saturday_halfday_cost'] = array(
    '#type' => 'textfield',
    '#size' => 3,
    '#maxlength' => 3,
    '#title' => t('Cost of Saturday Half Day Registration'),
    '#states' => array(
      'visible' => array(
        ':input[name="saturday_halfday_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#default_value' => variable_get('saturday_halfday_cost', '200'),
  );
  
  // Setup totals
  $form['setup_totals'] = array(
    '#type' => 'fieldset',
    '#title' => t('Option Totals Available Setup'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['setup_totals']['private_room_total'] = array(
    '#type' => 'textfield',
    '#title' => t('Total Number of Private Room Registrations Allowed'),
    '#size' => 3,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#default_value' => variable_get('private_room_total', '50'),
  );
  $form['setup_totals']['shared_room_total'] = array(
    '#type' => 'textfield',
    '#title' => t('Total Number of Shared Room Registrations Allowed'),
    '#size' => 3,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#default_value' => variable_get('shared_room_total', '50'),
  );
  $form['setup_totals']['commuter_total'] = array(
    '#type' => 'textfield',
    '#title' => t('Total Number of Commuter Registrations Allowed'),
    '#size' => 3,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#default_value' => variable_get('commuter_total', '13'),
  );
  $form['setup_totals']['saturday_commuter_total'] = array(
    '#type' => 'textfield',
    '#size' => 3,
    '#maxlength' => 3,
    '#title' => t('Total Number of Saturday Commuter Registrations Allowed'),
    '#states' => array(
      'visible' => array(
        ':input[name="saturday_commuter_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#default_value' => variable_get('saturday_commuter_total', '15'),
  );
  $form['setup_totals']['saturday_halfday_total'] = array(
    '#type' => 'textfield',
    '#size' => 3,
    '#maxlength' => 3,
    '#title' => t('Total Number of Saturday Half Day Registrations Allowed'),
    '#states' => array(
      'visible' => array(
        ':input[name="saturday_halfday_option"]' => array('value' => 'Yes'),
      ),
    ),
    '#required' => TRUE,
    '#default_value' => variable_get('saturday_halfday_total', '15'),
  );
        
  // Validate and save values
  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Update Configuration'),
    '#validate' => array('form_retreat_config_validate'),
    '#submit' => array('form_retreat_config_submit'),
  );
  
  return $form;
}

/*
 * Validate the config values (email, dates).
 */
function form_retreat_config_validate($form, &$form_state) {

  if (!valid_email_address($form_state['values']['retreat_coordinator_email'])) {
    form_set_error('retreat_coordinator_email', t('Please enter a valid retreat coordinator email address.'));
  }
  
  if (!verify_date_retreat_config($form_state['values']['retreat_earlybird_deadline'])) {
    form_set_error('retreat_earlybird_deadline', t('Please enter a valid early bird deadline.'));
  }
  
  if (!verify_date_retreat_config($form_state['values']['retreat_lodging_deadline'])) {
    form_set_error('retreat_lodging_deadline', t('Please enter a valid lodging deadline.'));
  }
  
  if (!verify_date_retreat_config($form_state['values']['retreat_commuter_deadline'])) {
    form_set_error('retreat_commuter_deadline', t('Please enter a valid commuter deadline.'));
  }
  
  if (!verify_date_retreat_config($form_state['values']['retreat_date'])) {
    form_set_error('retreat_date', t('Please enter a valid retreat date.'));
  }

  if (!is_numeric($form_state['values']['private_room_cost'])) {  
    form_set_error('private_room_cost', t('Please enter a valid private room cost.'));
  }

  if (!is_numeric($form_state['values']['shared_room_cost'])) {  
    form_set_error('shared_room_cost', t('Please enter a valid shared room cost.'));
  }

  if (!is_numeric($form_state['values']['commuter_cost'])) {  
    form_set_error('commuter_cost', t('Please enter a valid commuter cost.'));
  }

  if (!is_numeric($form_state['values']['private_rm_earlybird_cost'])) {  
    form_set_error('earlybird_cost', t('Please enter a valid early bird cost.'));
  }

  if (!is_numeric($form_state['values']['shared_rm_earlybird_cost'])) {  
    form_set_error('earlybird_cost', t('Please enter a valid early bird cost.'));
  }

  if (!is_numeric($form_state['values']['commuter_earlybird_cost'])) {  
    form_set_error('earlybird_cost', t('Please enter a valid early bird cost.'));
  }

  if (!is_numeric($form_state['values']['commuter_total'])) {
    form_set_error('commuter_total', t('Please enter a valid commuter total.'));
  }  

  if (!is_numeric($form_state['values']['saturday_commuter_total'])) {
    form_set_error('saturday_commuter_total', t('Please enter a valid Saturday commuter total.'));
  }  

  if (!is_numeric($form_state['values']['saturday_commuter_cost'])) {
    form_set_error('saturday_commuter_cost', t('Please enter a valid Saturday commuter cost.'));
  }  

  if (!is_numeric($form_state['values']['saturday_halfday_total'])) {
    form_set_error('saturday_halfday_total', t('Please enter a valid Saturday half day total.'));
  }  

  if (!is_numeric($form_state['values']['saturday_halfday_cost'])) {
    form_set_error('saturday_halfday_cost', t('Please enter a valid Saturday half day cost.'));
  }  

  if (!is_numeric($form_state['values']['retreat_earlybird_deadline_time'])) {
    form_set_error('retreat_earlybird_deadline_time', t('Please enter a valid Earlybird deadline time (numbers only).'));
  } else if (!($form_state['values']['retreat_earlybird_deadline_time'] >= 0 && $form_state['values']['retreat_earlybird_deadline_time'] <=24)) {
    form_set_error('retreat_earlybird_deadline_time', t('Please enter a valid Earlybird deadline time (0 to 24 only).'));
  }

  if (!is_numeric($form_state['values']['retreat_lodging_deadline_time'])) {
    form_set_error('retreat_lodging_deadline_time', t('Please enter a valid Lodging deadline time (numbers only).'));
  } else if (!($form_state['values']['retreat_lodging_deadline_time'] >= 0 && $form_state['values']['retreat_lodging_deadline_time'] <=24)) {
    form_set_error('retreat_lodging_deadline_time', t('Please enter a valid Lodging deadline time (0 to 24 only).'));
  }

  if (!is_numeric($form_state['values']['retreat_commuter_deadline_time'])) {
    form_set_error('retreat_commuter_deadline_time', t('Please enter a valid Commuter deadline time (numbers only).'));
  } else if (!($form_state['values']['retreat_commuter_deadline_time'] >= 0 && $form_state['values']['retreat_commuter_deadline_time'] <=24)) {
    form_set_error('retreat_commuter_deadline_time', t('Please enter a valid Commuter deadline time (0 to 24 only).'));
  }  
}

/*
 * Save config values.
 */
function form_retreat_config_submit($form, &$form_state) {

  // Save the values
  variable_set('retreat_year', $form_state['values']['retreat_year']);
  variable_set('retreat_email_subject', $form_state['values']['retreat_email_subject']);
  variable_set('retreat_title', $form_state['values']['retreat_title']);
  variable_set('retreat_coordinator', $form_state['values']['retreat_coordinator']);
  variable_set('retreat_coordinator_email', $form_state['values']['retreat_coordinator_email']);
  variable_set('retreat_coordinator_phone', $form_state['values']['retreat_coordinator_phone']);
  variable_set('retreat_coordinator_address_line1', $form_state['values']['retreat_coordinator_address_line1']);
  variable_set('retreat_coordinator_address_line2', $form_state['values']['retreat_coordinator_address_line2']);
  variable_set('retreat_date', $form_state['values']['retreat_date']);
  variable_set('retreat_earlybird_deadline', $form_state['values']['retreat_earlybird_deadline']);
  variable_set('retreat_earlybird_deadline_time', $form_state['values']['retreat_earlybird_deadline_time']);
  variable_set('retreat_lodging_deadline', $form_state['values']['retreat_lodging_deadline']);
  variable_set('retreat_lodging_deadline_time', $form_state['values']['retreat_lodging_deadline_time']);
  variable_set('retreat_commuter_deadline', $form_state['values']['retreat_commuter_deadline']);
  variable_set('retreat_commuter_deadline_time', $form_state['values']['retreat_commuter_deadline_time']);
  variable_set('retreat_closed_msg', $form_state['values']['retreat_closed_msg']);
  variable_set('private_room_cost', $form_state['values']['private_room_cost']);
  variable_set('private_room_total', $form_state['values']['private_room_total']);
//  variable_set('shared_bathroom_cost', $form_state['values']['shared_bathroom_cost']);
  variable_set('shared_room_cost', $form_state['values']['shared_room_cost']);
  variable_set('shared_room_total', $form_state['values']['shared_room_total']);
  variable_set('commuter_cost', $form_state['values']['commuter_cost']);
  variable_set('private_rm_earlybird_cost', $form_state['values']['private_rm_earlybird_cost']);
  variable_set('shared_rm_earlybird_cost', $form_state['values']['shared_rm_earlybird_cost']);
  variable_set('commuter_earlybird_cost', $form_state['values']['commuter_earlybird_cost']);
  variable_set('commuter_total', $form_state['values']['commuter_total']);
  variable_set('saturday_commuter_option', $form_state['values']['saturday_commuter_option']);
  variable_set('saturday_commuter_total', $form_state['values']['saturday_commuter_total']);
  variable_set('saturday_commuter_cost', $form_state['values']['saturday_commuter_cost']);
  variable_set('saturday_halfday_option', $form_state['values']['saturday_halfday_option']);
  variable_set('saturday_halfday_total', $form_state['values']['saturday_halfday_total']);
  variable_set('saturday_halfday_cost', $form_state['values']['saturday_halfday_cost']);

  // variable_set('option_2_option', $form_state['values']['option_2_option']);
  variable_set('eb_option', $form_state['values']['eb_option']);
  variable_set('lodging_deadline_option', $form_state['values']['lodging_deadline_option']);

  variable_set('scholarship_option', $form_state['values']['scholarship_option']);
  variable_set('display_scholarship_option', $form_state['values']['display_scholarship_option']);
  
  drupal_set_message(t('The new configuration has been saved'));
  
}

/*
 * Validate the dates entered.  Must be 5 (MM/DD) characters.
 */
function verify_date_retreat_config ($date) {

  $valid = TRUE;
  $month = 0;
  $day = 0;

  // Date will be in the form of mm/dd or mm/dd/yy
  $length = strlen($date);
  
  // Extract the number values
  if ($length == 5) {
    $month = substr($date, 0, 2);
    $day = substr($date, 3, 2);
  }
  
  // Verify the values
  if ((!($length == 5)) ||
      (!(is_numeric($month) && ($month >= 1 && $month <= 12))) ||
      (!(is_numeric($day) && ($day >= 1 && $day <= 31)))) {
      
    $valid = FALSE;
  }

  return $valid;  
}

