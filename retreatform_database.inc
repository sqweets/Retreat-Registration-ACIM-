<?php

/**
 *
 * This file has the database functions for the
 * RetreatForm module
 * 
 * OPTION_1, OPTION_2, OPTION_3, OPTION_4 and OPTION_5 are defined
 * in the retreatform_defines.inc file.
 */

require_once("retreatform_defines.inc");
require_once("retreatform_utilities.inc");
 
// This controls when the last shared room is taken but the second person has not registered yet
// $GLOBALS['only_roommate_names'] = FALSE;
static $only_roommate_names = FALSE;

/**
 * Computes the number of option 1 slots available.
 */
function option1_remaining() {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_1, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');

  $result = $query->count()->execute();
  
  $result = check_plain(OPTION_1_TOTAL - $result);
  
  return $result;

}

/**
 * Computes the number of option 2 slots available.
 */
// function option2_remaining() {

//   $query = new EntityFieldQuery();
//   $query->entityCondition('entity_type', 'node')
//     ->entityCondition('bundle', 'retreat_registration')
//     ->propertyCondition('status', 1)
//     ->fieldCondition('field_room_option', 'value', OPTION_2, '=')
//     ->fieldCondition('field_cancelled', 'value', 0, '=')
//     ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');

//   $result = $query->count()->execute();
  
//   $result = check_plain(options_totals('OPTION_2') - $result);
  
//   return $result;

// }

/**
 * Computes the number of option 3 slots available.
 */
function option3_remaining() {

  global $only_roommate_names;

  $query_total = new EntityFieldQuery();
  $query_total->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_3, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');
 
  $result_total = $query_total->count()->execute();
  
  $query_not_matched = new EntityFieldQuery();
  $query_not_matched->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_3, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=')
    ->fieldCondition('field_roommate', 'value', 'not matched', '=');
 
  $result_not_matched = $query_not_matched->count()->execute();
  
  $result = check_plain((OPTION_3_TOTAL * 2) - $result_total);
  
  if ($result == 0) {
    // All registrations taken
    $only_roommate_names = FALSE;
  } else if (($result != 0) && (($result_total + $result_not_matched) == (OPTION_3_TOTAL * 2))) {
    // No open roommate registrations left
    $only_roommate_names = TRUE;
  }
  
  return $result;
}

/**
 * Computes the number of option 4 slots available.
 */
function option4_remaining() {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_4, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');

  $result = $query->count()->execute();
  
  $result = check_plain(OPTION_4_TOTAL - $result);
  
  return $result;

}

/**
 * Computes the number of option 5 slots available.
 */
function option5_remaining() {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_5, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');

  $result = $query->count()->execute();
  
  $result = check_plain(OPTION_5_TOTAL - $result);
  
  return $result;

}

/**
 * Computes the number of option 6 slots available.
 */
function option6_remaining() {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_6, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');

  $result = $query->count()->execute();
  
  $result = check_plain(OPTION_6_TOTAL - $result);
  
  return $result;

}

/**
 * Computes the number of option 1 registrations.
 */
function option1_registrations() {

  $query_total = new EntityFieldQuery();
  $query_total->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_1, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');
 
  $result = $query_total->count()->execute();
  
  return $result;

}

/**
 * Computes the number of option 2 registrations.
 */
// function option2_registrations() {

//   $query_total = new EntityFieldQuery();
//   $query_total->entityCondition('entity_type', 'node')
//     ->entityCondition('bundle', 'retreat_registration')
//     ->propertyCondition('status', 1)
//     ->fieldCondition('field_room_option', 'value', OPTION_2, '=')
//     ->fieldCondition('field_cancelled', 'value', 0, '=')
//     ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');
 
//   $result = $query_total->count()->execute();
  
//   return $result;

// }

/**
 * Computes the number of option 3 registrations.
 */
function option3_registrations() {

  $query_total = new EntityFieldQuery();
  $query_total->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_3, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');
 
  $result = $query_total->count()->execute();
  
  return $result;

}

/**
 * Computes the number of option 4 registrations.
 */
function option4_registrations() {

  $query_total = new EntityFieldQuery();
  $query_total->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_4, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');
 
  $result = $query_total->count()->execute();
  
  return $result;

}

/**
 * Computes the number of option 5 registrations.
 */
function option5_registrations() {

  $query_total = new EntityFieldQuery();
  $query_total->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_5, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');
 
  $result = $query_total->count()->execute();
  
  return $result;

}

/**
 * Computes the number of option 6 registrations.
 */
function option6_registrations() {

  $query_total = new EntityFieldQuery();
  $query_total->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_6, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');
 
  $result = $query_total->count()->execute();
  
  return $result;

}

/**
 * Returns an array of unmatched roommates.
 */
function options_roommates() {

  global $only_roommate_names;

  $option_items_nids = array();
  $option_items = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_room_option', 'value', OPTION_3, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_roommate', 'value', 'not matched', '=');
 
  $result = $query->execute();
  
  if (isset($result['node'])) {
    $option_items_nids = array_keys($result['node']);
    $option_items = entity_load('node', $option_items_nids);
  }

  if ($only_roommate_names == FALSE) {  
    $roommates = array(
      'not matched' => t('My roommate has not registered yet'));
  } else {
    $roommates = array();
  }
  
  if (!(empty($option_items))) {
    foreach($option_items as $key => $value) {
      $first = field_get_items('node', $value, 'field_first_name');
      $last = field_get_items('node', $value, 'field_last_name');
      $string = $first[0]['value'] . ' ' . $last[0]['value'];
      $roommates[$key] = check_plain($string);
    }
  }

  return $roommates;

}

/**
 * Takes the new shared room registration and matches the names
 * and adds the node IDs of each roommate to the others regstration.
 *
 * The new roommate name is returned to update the form data so it is
 * available when the emails are sent out.
 */
function match_roommates($new_node) {
  $new_node_roommate_id = $new_node->field_roommate[$new_node->language][0]['value'];
  $new_node_id = $new_node->nid;
  
  // Save id in matched field
  $new_node->field_shared_room_matched[$new_node->language][0]['value'] = $new_node_roommate_id;
  
  // Get existing roommate node
  $existing_node = new stdClass();
  $existing_node = node_load($new_node_roommate_id);

  // Get existing name of roommate  
  $existing_first_name = $existing_node->field_first_name[$existing_node->language][0]['value'];
  $existing_last_name = $existing_node->field_last_name[$existing_node->language][0]['value'];
  $existing_name = $existing_first_name . ' ' . $existing_last_name;
  
  // Save save roommate name in new node
  $new_node->field_roommate[$new_node->language][0]['value'] = $existing_name;
  
  // Save new node id in existing matched field
  $existing_node->field_shared_room_matched[$existing_node->language][0]['value'] = $new_node_id;
  
  // Get name of new node  
  $new_node_first_name = $new_node->field_first_name[$new_node->language][0]['value'];
  $new_node_last_name = $new_node->field_last_name[$new_node->language][0]['value'];
  $new_node_name = $new_node_first_name . ' ' . $new_node_last_name;
  
  // Save save roommate name in existing node
  $existing_node->field_roommate[$existing_node->language][0]['value'] = $new_node_name;
  
  // Save updated nodes
  node_save($new_node);
  node_save($existing_node);
  
  return $existing_name;
}

/**
 * Takes the first name, last name and email address and searches for
 * an existing entry with the same values.
 */
function match_entry($identity) {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=')
    ->fieldCondition('field_first_name', 'value', $identity['first'], '=')
    ->fieldCondition('field_last_name', 'value', $identity['last'], '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_email_address', 'value', $identity['email'], '=');
 
  $result = $query->count()->execute();
  
  return $result;
}

/**
 * Computes the number of mail registrations.
 */
function total_mail() {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_form_payment', 'value', 'Mail', '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');

  $result = $query->count()->execute();
  
  return $result;

}

/**
 * Computes the number of paypal registrations.
 */
function total_paypal() {

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_form_payment', 'value', 'PayPal', '=')
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');

  $result = $query->count()->execute();
  
  return $result;

}

/**
 * Computes an array of all registrants. Alphabetical based on last name
 */
function all_registrants_by_last_name() {
  $names_nids = array();
  $names = array();

  // Get all the registrations that haven't been cancelled
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'retreat_registration')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_cancelled', 'value', 0, '=')
    ->fieldCondition('field_year_of_retreat', 'value', YEAR, '=');

  $result = $query->execute();

  if (isset($result['node'])) {
    $names_nids = array_keys($result['node']);
    $names = entity_load('node', $names_nids);
  }
  
  // Create an alphabetical array of the names (last, first) with the node id as the key
  if (!(empty($names))) {
    foreach($names as $key => $value) {
      $title = $value->title;
      $node_id = $value->nid;
      $name_list[$node_id] = check_plain($title);  //make the key the node id here
    }
 
    asort($name_list);
  }
  
  return $name_list;
}

/**
 * Returns an array sorted by room number (which is the key), ascending
 */
function get_sorted_room_listing () {
  // Get room listing
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'mc_room')
    ->propertyCondition('status', 1);
 
  $result = $query->execute();
  
  if (isset($result['node'])) {
    $rooms_nids = array_keys($result['node']);
    $rooms = entity_load('node', $rooms_nids);
  }
  
  if (!(empty($rooms))) {
    foreach($rooms as $key => $value) {
      $room_number = field_get_items('node', $value, 'field_mc_room_integer');

      $available = field_get_items('node', $value, 'field_available2');
      $assignable = field_get_items('node', $value, 'field_available');
      $room_type = field_get_items('node', $value, 'field_room_type');
      $connecting_room = field_get_items('node', $value, 'field_connecting_room');
      $number_of_beds = field_get_items('node', $value, 'field_number_of_beds');
      $handicapped = field_get_items('node', $value, 'field_handicapped');
      $elevator = field_get_items('node', $value, 'field_elevator');

      $room_array[$room_number[0]['value']] = array(
            'available' => $available[0]['value'],
            'assignable' => $assignable[0]['value'],
            'room_type' => $room_type[0]['value'],
            'connecting_room' => $connecting_room[0]['value'],
            'number_of_beds' => $number_of_beds[0]['value'],
            'handicapped' => $handicapped[0]['value'],
            'elevator' => $elevator[0]['value'],
            );
    }
    
    // Sort the array on the room number
    ksort($room_array);
  }

  return $room_array;
}
