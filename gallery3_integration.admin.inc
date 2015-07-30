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

	$form['gallery3_integration_galler3_groups'] = array(
		'#type' => 'textarea',
		'#title' => t('Gallery3 groups, not editable'),
		'#rows' => count(get_gallery3_groups())+1,
		'#default_value' => gallery3_integration_build_groups_textfiled(),
		'#description' => t('This are all the groups presents in the gallery3 db'),
		'#required' => FALSE,
		// '#disabled' => TRUE,


	);
	return system_settings_form($form);

}

function gallery3_integration_build_groups_textfiled(){
	$groups_string="";
	foreach (get_gallery3_groups() as $group_name => $id) {
		$groups_string .= $group_name.": ".$id."\n";
	}

	return $groups_string;


}
