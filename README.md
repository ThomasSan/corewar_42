########### VM #############

#init_vm
	#check_arg
		gestion_options
		count_champions
	#init_memory
		malloc de MEM_SIZE
	#init_champions
		#fill_champ
			#read_champ_content
				len_champ
			#read_header
				magic/progsize/comment/progname
			#read_size
				CHAMP_MAX_SIZE
	#place_champions
		attrib de la memoire / champion --  (MEM_SIZE / nb champ)
#start_fight
	#init_cycle
		#init_processes
			#init_process
				#init_register
	#if graph == 1 -> show_game
		plus tard
	#else mem_dump
		rempli la mem de 0 | \n tous les 32 parcouru
	#fight
		#exec_process
			#trytoexec
				#if il reste des cycles
					#exec_op (op == live/zjmp etc..)
						#get_param
							get_pcode
							get_size_param
						#check_param
				#sinon
					stop
		#update_cycle
		#if graphics == 1
			update l'affichage
	#del_cycle
