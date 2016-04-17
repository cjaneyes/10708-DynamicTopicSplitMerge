function func = ourf_bundle_func

func.iterate   = @hdp_ourf_iterate;
func.predict   = [];
func.numitems  = @ourf_numitems;
func.newclass  = @ourf_newclass;
func.additem   = @ourf_additem;
func.additems  = @ourf_additems;
func.delitem   = @ourf_delitem;
func.delitems  = @ourf_delitems;

