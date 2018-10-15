<?php

/**
 * This file has the "utility" functions for the
 * RetreatForm module
 * 
 * OPTION_1, OPTION_2, OPTION_3 and OPTION_4 are defined
 * in the retreatform_form.inc file.
 */

require_once("retreatform_defines.inc");

/*
 * Returns room description as a string.
 */
function room_str($option) {
  switch ($option) {
    case 'OPTION_1':
      $result = substr(OPTION_1, 0);
      break;
    // case 'OPTION_2':
    //   $result = substr(OPTION_2, 0);
    //   break;
    case 'OPTION_3':
      $result = substr(OPTION_3, 0);
      break;
    case 'OTHER':
      $result = 'guest room';
  }
  return $result;
}

/**
 * Returns dollar value based on room option.
 */
function room_costs($option) {
  // check to see if early bird deadline past
  $apply_eb_rate = compute_eb_deadline_met();
  
  $payment = 0;
  switch ($option) {
    case OPTION_1:
      if ($apply_eb_rate == 'Yes' && EB_OPTION == 'Yes') {
        $payment = OPTION_1_COST + PRIVATE_RM_EB_COST;
      } else {
        $payment = OPTION_1_COST;
      }
      break;
    // case OPTION_2:
    //   if ($apply_eb_rate == 'Yes' && EB_OPTION == 'Yes') {
    //     $payment = OPTION_2_COST + EB_COST;
    //   } else {
    //     $payment = OPTION_2_COST;
    //   }
    //   break;
    case OPTION_3:
      if ($apply_eb_rate == 'Yes' && EB_OPTION == 'Yes') {
        $payment = OPTION_3_COST + SHARED_RM_EB_COST;
      } else {
        $payment = OPTION_3_COST;
      }
      break;
    case OPTION_4:
      if ($apply_eb_rate == 'Yes' && EB_OPTION == 'Yes') {
        $payment = OPTION_4_COST + COMMUTER_EB_COST;
      } else {
        $payment = OPTION_4_COST;
      }
      break;
    case OPTION_5:
      $payment = OPTION_5_COST;
      break;
    case OPTION_6:
      $payment = OPTION_6_COST;
      break;
  }
  return $payment;
}

/**
 * Options list for selection of room option.
 */
function options_rooms() {

  if (RETREAT_LODGING_REG_MET == 'Yes' && LODGING_DEADLINE_OPTION == 'Yes') {
    if (SATURDAY == 'Yes' && HALFDAY == 'Yes') {
      return array(
        OPTION_4 => t(OPTION_4),
        OPTION_5 => t(OPTION_5),
        OPTION_6 => t(OPTION_6),
      );
    } else if (HALFDAY == 'Yes' && SATURDAY == 'No') {
      return array(
        OPTION_4 => t(OPTION_4),
        OPTION_6 => t(OPTION_4),
      );
    } else if (HALFDAY == 'No' && SATURDAY == 'Yes') {
      return array(
        OPTION_4 => t(OPTION_4),
        OPTION_5 => t(OPTION_5),
      );
    } else {
      return array(
        OPTION_4 => t(OPTION_4),
      );
    }
  } 
  
  if (HALFDAY == 'Yes') {
    if (SATURDAY == 'No' && OPT_2_OPTION == 'No') {
      return array(
        OPTION_1 => t(OPTION_1),
        OPTION_3 => t(OPTION_3),
        OPTION_4 => t(OPTION_4),
        OPTION_6 => t(OPTION_6),
      );
    } else if (SATURDAY == 'Yes' && OPT_2_OPTION == 'No') {
      return array(
        OPTION_1 => t(OPTION_1),
        OPTION_3 => t(OPTION_3),
        OPTION_4 => t(OPTION_4),
        OPTION_5 => t(OPTION_5),
        OPTION_6 => t(OPTION_6),
      );
    }
    // } else if (SATURDAY == 'No' && OPT_2_OPTION == 'Yes') {
    //   return array(
    //     OPTION_1 => t(OPTION_1),
    //     OPTION_2 => t(OPTION_2),
    //     OPTION_3 => t(OPTION_3),
    //     OPTION_4 => t(OPTION_4),
    //     OPTION_6 => t(OPTION_6),
    //   );
    // } else if (SATURDAY == 'Yes' && OPT_2_OPTION == 'Yes') {
    //   return array(
    //     OPTION_1 => t(OPTION_1),
    //     OPTION_2 => t(OPTION_2),
    //     OPTION_3 => t(OPTION_3),
    //     OPTION_4 => t(OPTION_4),
    //     OPTION_5 => t(OPTION_5),
    //     OPTION_6 => t(OPTION_6),
    //   );
    // }
  } else {
    // if (SATURDAY == 'No' && OPT_2_OPTION == 'No') {
    if (SATURDAY == 'No') {
      return array(
        OPTION_1 => t(OPTION_1),
        OPTION_3 => t(OPTION_3),
        OPTION_4 => t(OPTION_4),
      );
    } else if (SATURDAY == 'Yes') {
      return array(
        OPTION_1 => t(OPTION_1),
        OPTION_3 => t(OPTION_3),
        OPTION_4 => t(OPTION_4),
        OPTION_5 => t(OPTION_5),
      );
    }
    // } else if (SATURDAY == 'No' && OPT_2_OPTION == 'Yes') {
    //   return array(
    //     OPTION_1 => t(OPTION_1),
    //     OPTION_2 => t(OPTION_2),
    //     OPTION_3 => t(OPTION_3),
    //     OPTION_4 => t(OPTION_4),
    //   );
    // } else if (SATURDAY == 'Yes' && OPT_2_OPTION == 'Yes') {
    //   return array(
    //     OPTION_1 => t(OPTION_1),
    //     OPTION_2 => t(OPTION_2),
    //     OPTION_3 => t(OPTION_3),
    //     OPTION_4 => t(OPTION_4),
    //     OPTION_5 => t(OPTION_5),
    //   );
    // }
  }
}

/**
 * Options list for meal reguirements.
 */
function options_meal() {
  return array(
    'None' => t('None'),
    'Vegetarian' => t('Vegetarian'),
    'Gluten Free' => t('Gluten Free'),
    'Diabetic' => t('Diabetic'),
    'Other (please explain)' => t('Other (please explain)'),
  );
}

/**
 * Options list for payment options.
 */
function options_payment() {
  if (DISPLAY_SCHOLARSHIP_OPTION == 'No') {
    return array(
      'PayPal' => t('Pay online via PayPal (credit cards accepted)'),
      'Mail' => t('Print email form and mail with payment'),
    );
  } else {
    return array(
      'PayPal' => t('Pay online via PayPal (credit cards accepted)'),
      'Mail' => t('Print email form and mail with payment'),
      'Scholarship' => t('Request a scholarship'),
    );
  }
}

/**
 * Options list for how heard options.
 */
function options_how_heard() {
    return array(
      'Retreat Speaker' => t('Retreat Speaker\'s Correspondence'),
      'Miracles Magazine' => t('Miracles Magazine Ad'),
      'Newsletter' => t('ACIM St. Louis Newsletter'),
      'Study Group' => t('Study Group'),
      'Other' => t('Other'),
    );
}

/**
 * Returns the total number of option 1 rooms
 * using the rooms settings setup in the Manage
 * Rooms forms.  This will account for double rooms
 * being changed to singles.
 *
 * Returns the total number of option 3 rooms
 * If the room was changed from 2 beds to 1 in the
 * rooms settings it will not be counted as an
 * option 3 room.
 *
 * Returns the total number of option 2 rooms.
*/
function options_totals($option) {
  $first_floor_rooms = variable_get('first_floor_rooms');
  $second_floor_rooms = variable_get('second_floor_rooms');
  $rooms = $first_floor_rooms + $second_floor_rooms;
  
  $count_1_bed = 0;
  $count_2_bed = 0;
  $count = 0;
  
  foreach($rooms as $key => $value) {

    // Room must be both available and assignable
    if ($value['available'] == 1 && $value['assignable'] == 1) {


      // Options out the window, option 1 count = 1 bed
      // option 3 count = 2 beds
      if ($value['number_of_beds'] == 1) {
        ++$count_1_bed;
      } else {
        ++$count_2_bed;
      }


/*
      // Count the number of the requested room type
      if ($option == $value['room_type']) {
        ++$count;
      }
        
      // If counting OPTION_1 rooms, add all OPTION_3 rooms set to 1 bed
      if (($option == 'OPTION_1') && (($value['room_type'] == 'OPTION_3') && ($value['number_of_beds'] == 1))) {
        ++$count;
      }
      
      // If counting OPTION_3 rooms, subtract all OPTION_3 rooms set to 1 bed
      if (($option == 'OPTION_3') && (($value['room_type'] == 'OPTION_3') && ($value['number_of_beds'] == 1))) {
        --$count;
      }

      // The guest room is considered an option 1 room    
      if (($option == 'OPTION_1') && ($value['room_type'] == 'OTHER')) {
        ++$count;
      } */
    }
  }
  
  if ($option == 'OPTION_1') {
    $count = $count_1_bed;
  } elseif ($option == 'OPTION_3') {
    $count = $count_2_bed;
  }

  return $count;
}

/**
 * Options list containing United States states and territories.
 */
function options_united_states() {
  return array(
    'AL' => t('Alabama'),
    'AK' => t('Alaska'),
    'AS' => t('American Samoa'),
    'AZ' => t('Arizona'),
    'AR' => t('Arkansas'),
    'CA' => t('California'),
    'CO' => t('Colorado'),
    'CT' => t('Connecticut'),
    'DE' => t('Delaware'),
    'DC' => t('District of Columbia'),
    'FL' => t('Florida'),
    'GA' => t('Georgia'),
    'GU' => t('Guam'),
    'HI' => t('Hawaii'),
    'ID' => t('Idaho'),
    'IL' => t('Illinois'),
    'IN' => t('Indiana'),
    'IA' => t('Iowa'),
    'KS' => t('Kansas'),
    'KY' => t('Kentucky'),
    'LA' => t('Louisiana'),
    'ME' => t('Maine'),
    'MH' => t('Marshall Islands'),
    'MD' => t('Maryland'),
    'MA' => t('Massachusetts'),
    'MI' => t('Michigan'),
    'MN' => t('Minnesota'),
    'MS' => t('Mississippi'),
    'MO' => t('Missouri'),
    'MT' => t('Montana'),
    'NE' => t('Nebraska'),
    'NV' => t('Nevada'),
    'NH' => t('New Hampshire'),
    'NJ' => t('New Jersey'),
    'NM' => t('New Mexico'),
    'NY' => t('New York'),
    'NC' => t('North Carolina'),
    'ND' => t('North Dakota'),
    'MP' => t('Northern Marianas Islands'),
    'OH' => t('Ohio'),
    'OK' => t('Oklahoma'),
    'OR' => t('Oregon'),
    'PW' => t('Palau'),
    'PA' => t('Pennsylvania'),
    'PR' => t('Puerto Rico'),
    'RI' => t('Rhode Island'),
    'SC' => t('South Carolina'),
    'SD' => t('South Dakota'),
    'TN' => t('Tennessee'),
    'TX' => t('Texas'),
    'UT' => t('Utah'),
    'VT' => t('Vermont'),
    'VI' => t('Virgin Islands'),
    'VA' => t('Virginia'),
    'WA' => t('Washington'),
    'WV' => t('West Virginia'),
    'WI' => t('Wisconsin'),
    'WY' => t('Wyoming'),
  );
}
