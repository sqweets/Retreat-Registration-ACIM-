<?php

/**
 * This form displays the current totals for each option
 * as well as total overall
 *
 */

require_once("retreatform_defines.inc");
require_once("retreatform_database.inc");
  
function form_current_totals($form, &$form_state) {

  $total_1 = option1_registrations();
  // $total_2 = option2_registrations();
  $total_3 = option3_registrations();
  $total_4 = option4_registrations();
  $total_5 = option5_registrations();
  $total_6 = option6_registrations();

  // include option 5 only if there is an option 5 (saturday commuter)
  // same for option 6
  if (SATURDAY == 'Yes' && HALFDAY == 'Yes') {
//    $total = $total_1 + $total_2 + $total_3 + $total_4 + $total_5 + $total_6;
    $total = $total_1 + $total_3 + $total_4 + $total_5 + $total_6;
  } else if (SATURDAY == 'Yes' && HALFDAY == 'No') {
    // $total = $total_1 + $total_2 + $total_3 + $total_4 + $total_5;
    $total = $total_1 + $total_3 + $total_4 + $total_5;
  } else if (SATURDAY == 'No' && HALFDAY == 'Yes') {
    // $total = $total_1 + $total_2 + $total_3 + $total_4 + $total_6;
    $total = $total_1 + $total_3 + $total_4 + $total_6;
  } else {
    // $total = $total_1 + $total_2 + $total_3 + $total_4;
    $total = $total_1 + $total_3 + $total_4;
  }

  $form['info_text'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t("<u>Totals do not include cancelled registrations</u>\n&nbsp;"),
  );

  $form['option_1_total'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('Private Room: @total', array('@total' => $total_1)),
  );

  // if (OPT_2_OPTION == 'Yes') {
  //   $form['option_2_total'] = array(
  //     '#prefix' => '<p style="text-align: left; font-weight: bold;">',
  //     '#suffix' => '</p>',
  //     '#markup' => t('Private Room shared bath: @total', array('@total' => $total_2)),
  //   );
  // }

  $form['option_3_total'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('Shared Room private bath: @total', array('@total' => $total_3)),
  );

  $form['option_4_total'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('Commuter: @total', array('@total' => $total_4)),
  );

  if (SATURDAY == 'Yes') {
    $form['option_5_total'] = array(
      '#prefix' => '<p style="text-align: left; font-weight: bold;">',
      '#suffix' => '</p>',
      '#markup' => t('Saturday Commuter: @total', array('@total' => $total_5)),
    );
  }

  if (HALFDAY == 'Yes') {
    $form['option_6_total'] = array(
      '#prefix' => '<p style="text-align: left; font-weight: bold;">',
      '#suffix' => '</p>',
      '#markup' => t('Saturday Half Day: @total', array('@total' => $total_6)),
    );
  }

  $form['total_mail'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('All Mail registrations: @total', array('@total' => total_mail())),
  );
  
  
  $form['total_paypal'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('All PayPal registrations: @total', array('@total' => total_paypal())),
  );

  $form['line'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('---------------------------------------------------'),
  );
  
  $form['all_total'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('Total registrations: @total', array('@total' => $total)),
  );

  $form['line2'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('---------------------------------------------------'),
  );
  
  $form['line3'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('<u>Current "available" numbers</u>'),
  );

  $form['option_1_available'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('Private Room: @remaining', array('@remaining' => option1_remaining())),
  );

  // if (OPT_2_OPTION == 'Yes') {
  //   $form['option_2_available'] = array(
  //     '#prefix' => '<p style="text-align: left; font-weight: bold;">',
  //     '#suffix' => '</p>',
  //     '#markup' => t('Private Room shared bath: @remaining', array('@remaining' => option2_remaining())),
  //   );
  // }

  $form['option_3_available'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('Shared Room private bath: @remaining', array('@remaining' => option3_remaining())),
  );

  $form['option_4_available'] = array(
    '#prefix' => '<p style="text-align: left; font-weight: bold;">',
    '#suffix' => '</p>',
    '#markup' => t('Commuter: @remaining', array('@remaining' => option4_remaining())),
  );

  if (SATURDAY == 'Yes') {
    $form['option_5_available'] = array(
      '#prefix' => '<p style="text-align: left; font-weight: bold;">',
      '#suffix' => '</p>',
      '#markup' => t('Saturday Commuter: @remaining', array('@remaining' => option5_remaining())),
    );
  }

  if (HALFDAY == 'Yes') {
    $form['option_6_available'] = array(
      '#prefix' => '<p style="text-align: left; font-weight: bold;">',
      '#suffix' => '</p>',
      '#markup' => t('Saturday Half Day: @remaining', array('@remaining' => option6_remaining())),
    );
  }

  return $form;
}
