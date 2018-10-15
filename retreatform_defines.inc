<?php

/*
*  This file contains the defines used by the rest of the module
*  as well as the date formatting and computation functions for
*  the early bird deadline and final deadline olus the functions
*  that compute the rooms available.
*
*/

define ('STR_FOR_COST', ', $');
define ('OPTION_1', 'Private room and bath');
// define ('OPTION_2', 'Private room shared bath');
define ('OPTION_3', 'Shared room private bath');
define ('OPTION_4', 'Commuters, no overnight lodging');
define ('OPTION_5', 'Saturday commuters, no overnight lodging');
define ('OPTION_6', 'Saturday Half Day commuters');

define ('YEAR', variable_get('retreat_year', '2013'));
define ('OPTION_1_COST', variable_get('private_room_cost', '325'));
// define ('OPTION_2_COST', variable_get('shared_bathroom_cost', '300'));
define ('OPTION_3_COST', variable_get('shared_room_cost', '275'));
define ('OPTION_4_COST', variable_get('commuter_cost', '200'));
define ('OPTION_5_COST', variable_get('saturday_commuter_cost', '50'));
define ('OPTION_6_COST', variable_get('saturday_halfday_cost', '30'));
define ('PRIVATE_RM_EB_COST', variable_get('private_rm_earlybird_cost', '50'));
define ('SHARED_RM_EB_COST', variable_get('shared_rm_earlybird_cost', '50'));
define ('COMMUTER_EB_COST', variable_get('commuter_earlybird_cost', '25'));

define ('RETREAT_TITLE', variable_get('retreat_title', 'Following Spirit without Hesitation'));
define ('RETREAT_SUBJECT', variable_get('retreat_email_subject', '2013 St. Louis ACIM Retreat With Regina Dawn Akers and Scott Grace'));
define ('RETREAT_COORD', variable_get('retreat_coordinator', 'Corinne Esneault'));
define ('RETREAT_COORD_EMAIL', variable_get('retreat_coordinator_email', 'cesneault@charter.net'));
define ('RETREAT_COORD_PHONE', variable_get('retreat_coordinator_phone', '314-843-0954'));
define ('RETREAT_COORD_ADDRESS_LINE1', variable_get('retreat_coordinator_address_line1', '10885 Ridge Forest Drive'));
define ('RETREAT_COORD_ADDRESS_LINE2', variable_get('retreat_coordinator_address_line2', 'St. Louis, MO  63123'));
define ('RETREAT_CLOSED_MSG', variable_get('retreat_closed_msg', ''));
define ('RETREAT_EB_DEADLINE', compute_eb_deadline_str());
define ('RETREAT_EB_DEADLINE_TIME', variable_get('retreat_earlybird_deadline_time'));
define ('RETREAT_LODGING_DEADLINE', compute_lodging_deadline_str());
define ('RETREAT_LODGING_DEADLINE_TIME', variable_get('retreat_lodging_deadline_time'));
define ('RETREAT_COMMUTER_DEADLINE', compute_commuter_deadline_str());
define ('RETREAT_COMMUTER_DEADLINE_TIME', variable_get('retreat_commuter_deadline'));
define ('RETREAT_EB_REG_MET', compute_eb_deadline_met());
define ('RETREAT_LODGING_REG_MET', compute_lodging_deadline_met());
define ('RETREAT_COMMUTER_REG_MET', compute_commuter_deadline_met());

//define ('RETREAT_SCHOLARSHIP_DEADLINE_MET', compute_scholarship_deadline_met());

define ('OPTION_1_TOTAL', variable_get('private_room_total', '50'));
define ('OPTION_3_TOTAL', variable_get('shared_room_total', '25'));
define ('OPTION_4_TOTAL', variable_get('commuter_total', '13'));


// Saturday commuter options
define ('SATURDAY', variable_get('saturday_commuter_option', 'Yes'));
define ('OPTION_5_TOTAL', variable_get('saturday_commuter_total', '15'));
define ('HALFDAY', variable_get('saturday_halfday_option', 'Yes'));
define ('OPTION_6_TOTAL', variable_get('saturday_halfday_total', '15'));

// Other options
// define ('OPT_2_OPTION', variable_get('option_2_option', 'Yes'));
define ('EB_OPTION', variable_get('eb_option', 'Yes'));
define ('LODGING_DEADLINE_OPTION', variable_get('lodging_deadline_option', 'Yes'));
define ('SCHOLARSHIP_OPTION', variable_get('scholarship_option', 'Yes'));
define ('DISPLAY_SCHOLARSHIP_OPTION', variable_get('display_scholarship_option', 'Yes'));


/*
* This function returns the ledging deadline date correctly formatted
*
*/
function compute_lodging_deadline_str() {
  $year = substr(YEAR, 0, 4);
  // These values in the form: MM/DD
  $lodging_deadline_raw = variable_get('retreat_lodging_deadline');
  $lodging_deadline_str = strtotime($lodging_deadline_raw . '/' . $year);
  
  // Format example: Friday, July 1st
  return date('l, F jS', $lodging_deadline_str);
}

/*
* This function returns the commuter deadline date correctly formatted
*
*/
function compute_commuter_deadline_str() {
  $year = substr(YEAR, 0, 4);
  // These values in the form: MM/DD
  $commuter_deadline_raw = variable_get('retreat_commuter_deadline');
  $commuter_deadline_str = strtotime($commuter_deadline_raw . '/' . $year);
  
  // Format example: Friday, July 1st
  return date('l, F jS', $commuter_deadline_str);
}

/*
* This function returns the early bird deadline date correctly formatted
*
*/
function compute_eb_deadline_str() {
  $year = substr(YEAR, 0, 4);
  // These values in the form: MM/DD
  $eb_deadline_raw = variable_get('retreat_earlybird_deadline');
  $eb_deadline_str = strtotime($eb_deadline_raw . '/' . $year);
  
  // Format example: Friday, July 1st
  return date('l, F jS', $eb_deadline_str);
}

/*
* This function returns lodging deadline met
*
*/
function compute_lodging_deadline_met() {
  $year = substr(YEAR, 0, 4);
  // These values in the form: MM/DD
  $lodging_deadline_raw = variable_get('retreat_lodging_deadline');
  $lodging_deadline_str = strtotime($lodging_deadline_raw . '/' . $year);
  
  $today = getdate();
  $today_str = strtotime($today['mon'] . '/' . $today['mday'] . '/' . $today['year']);

  // Get the hour of the deadline
  $lodging_deadline_time = variable_get('retreat_lodging_deadline_time');

  // Check date and time
  if ($lodging_deadline_str < $today_str) {
    $return_val = 'Yes';
  } else {
    if ($lodging_deadline_str == $today_str && $lodging_deadline_time <= $today['hours']) {
      $return_val = 'Yes';
    } else {
      $return_val = 'No';
    }
  }
  
  return $return_val;
}

/*
* This function returns commuter deadline met
*
*/
function compute_commuter_deadline_met() {
  $year = substr(YEAR, 0, 4);
  // These values in the form: MM/DD
  $commuter_deadline_raw = variable_get('retreat_commuter_deadline');
  $commuter_deadline_str = strtotime($commuter_deadline_raw . '/' . $year);
  
  $today = getdate();
  $today_str = strtotime($today['mon'] . '/' . $today['mday'] . '/' . $today['year']);
  
  // Get the hour of the deadline
  $commuter_deadline_time = variable_get('retreat_commuter_deadline_time');

  // Check date and time
  if ($commuter_deadline_str < $today_str) {
    $return_val = 'Yes';
  } else {
    if ($commuter_deadline_str == $today_str && $commuter_deadline_time <= $today['hours']) {
      $return_val = 'Yes';
    } else {
      $return_val = 'No';
    }
  }
  
  return $return_val;
}

/*
* This function returns early bird deadline met
* Its also called in the room_costs($option) function
*
*/
function compute_eb_deadline_met() {
  $year = substr(YEAR, 0, 4);
  // These values in the form: MM/DD
  $eb_deadline_raw = variable_get('retreat_earlybird_deadline');
  $eb_deadline_str = strtotime($eb_deadline_raw . '/' . $year);

  $today = getdate();
  $today_str = strtotime($today['mon'] . '/' . $today['mday'] . '/' . $today['year']);

  // Get the hour of the deadline
  $eb_deadline_time = variable_get('retreat_earlybird_deadline_time');

  // Check date and time
  if ($eb_deadline_str < $today_str) {
    $return_val = 'Yes';
  } else {
    if ($eb_deadline_str == $today_str && $eb_deadline_time <= $today['hours']) {
      $return_val = 'Yes';
    } else {
      $return_val = 'No';
    }
  }
  
  return $return_val;
}

/*
* This function determines if the deadline for scholarship applications has been met
*
*/
//function compute_scholarship_deadline_met() {
//
//  $event_date = variable_get('retreat_date');
//  $event_month = ltrim(substr($event_date, 0, 2), '0');
//  $event_day = ltrim(substr($event_date, 3, 2), '0');
//
//  $event_date_new = strtotime($event_month . '/' . $event_day . '/' . YEAR);
//
//  // Get the date 60 days from now
//  $today_plus_60 = strtotime("60 days");
//  
//  if ($today_plus_60 >= $event_date_new) {
//    $deadline_met = 'Yes';
//  } else {
//    $deadline_met = 'No';
//  }
//
//  return $deadline_met;
//}
