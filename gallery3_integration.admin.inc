<?php


function gallery3_integration_admin_form($form, $form_state){


	$form['gallery3_integration_db_prefix'] = array(
		'#type' => 'textfield',
		'#title' => t('Gallery3 tables prefixes'),
		'#size' => 20,
		'#maxlength' => 30,
		'#default_value'=> variable_get('gallery3_integration_db_prefix','g3_'),
		'#description' => t('The prefix of the gallery3 tables in the database.'.
			'Remember to add any underscore!'),
		'#required' => TRUE,

	);
	// dprint_r($form);

	//TODO: find a better way to show groups from gallery

	$form['gallery3_integration_gallery3_groups'] = array(
		'#type' => 'textarea',
		'#title' => t('Gallery3 groups, not editable'),
		'#rows' => count(get_gallery3_groups())+1,
		'#default_value' => gallery3_integration_build_groups_textfiled(),
		'#description' => t('This are all the groups presents in the gallery3 db'),
		'#required' => FALSE,
		// '#disabled' => TRUE,


	);

	$drupal_roles = user_roles();
	asort($drupal_roles);

	foreach ($drupal_roles as $id => $role) {
		//Skip admin and anonimous user and autenticated, this will be added automatically
		if ($id <= 3){
			continue;
		}
		$form['gallery3_integration_role_'.$id] = array(
		'#type' => 'select',
		'#title' => "Associate $role (id = $id) whit gallery3 role",
		'#default_value' => gallery3_integration_select_default($id),
		'#options' => get_gallery3_groups(),
		'#description' => 'Select a role in gallery3 for '.$role,


		);
	}
	return system_settings_form($form);

}

function gallery3_integration_build_groups_textfiled(){
	$groups_string="";
	foreach (get_gallery3_groups() as $id => $name) {
		$groups_string .= $name." : ".$id."\n";
	}

	return $groups_string;
}

function gallery3_integration_select_default($id){

	$variable = variable_get('gallery3_integration_role_'.$id);

	if (empty($variable)){
		return 1;

	}
	return variable_get('gallery3_integration_role_'.$id);
}

