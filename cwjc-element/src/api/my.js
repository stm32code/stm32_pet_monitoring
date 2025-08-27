import request from '@/utils/request'
import {
	getToken
} from '@/utils/auth';
export default {

	admin_user_list() {
		return request({
			url: '/auth/admin_user_list',
			method: 'get',
			params: {}
		})
	},
	delUserAxios(uid) {
		return request({
			url: '/auth/del_user_by_id',
			method: 'get',
			params: {
				uid: uid
			}
		})
	},
	getUserInfoByUidAxios(uid) {
		return request({
			url: '/auth/get_user_by_id',
			method: 'get',
			params: {
				uid: uid
			}
		})
	},

	updateUserInfoAxios(uid, uname, upwd, urole, rname, email, phone) {
		return request({
			url: '/auth/update_user_by_id',
			method: 'get',
			params: {
				uid: uid,
				uname: uname,
				upwd: upwd,
				urole: urole,
				rname: rname,
				email: email,
				phone: phone,
			}
		})
	},

	addUserAxios(uname, upwd, urole,rname,email,phone) {
		return request({
			url: '/auth/register',
			method: 'get',
			params: {
				uname: uname,
				upwd: upwd,
				urole: urole,
				rname: rname,
				email: email,
				phone: phone,
			}
		})
	},

	//获取历史数据
	getHistData(page) {
		return request({
			url: '/auth/get_history',
			method: 'get',
			params: {
				page: page,
			}
		})
	},
	get_war_history(page) {
		return request({
			url: '/auth/get_war_history',
			method: 'get',
			params: {
				page: page,
			}
		})
	},
	save_file(imgSrc) {
		return request({
			url: '/util/uploadFile',
			method: 'post',
			params: {
				file: imgSrc
			},
			headers: {
				'Content-Type': 'multipart/form-data'
			}
		})
	},
	//意见反馈
	commentsSet(cname, cphone, cMsg) {
		return request({
			url: '/auth/comments_set',
			method: 'get',
			params: {
				cname: cname,
				cphone: cphone,
				cMsg: cMsg
			}
		})
	},
	//获取意见反馈内容
	getCommentsData(page) {
		return request({
			url: '/auth/comments_get',
			method: 'get',
			params: {
				page: page,
			}
		})
	},
	//获取操作记录
	getOperationData(page) {
		return request({
			url: '/auth/get_operation',
			method: 'get',
			params: {
				page: page,
			}
		})
	},
	//获取操作记录
	getWarningData(page) {
		return request({
			url: '/auth/get_warning',
			method: 'get',
			params: {
				page: page,
			}
		})
	},
	//根据id删除
	delWarningAxios(id) {
		return request({
			url: '/auth/del_warning',
			method: 'get',
			params: {
				id: id
			}
		})
	},
	//获取实时数据
	getCurrData() {
		return request({
			url: '/auth/get_curr_data',
			method: 'get',
			params: {}
		})
	},
	//设备控制get
	getContro() {
		return request({
			url: '/auth/get_con',
			method: 'get',
			params: {}
		})
	},
	//设备控制set
	setContro(name, value) {
		return request({
			url: '/auth/set_con',
			method: 'get',
			params: {
				name: name,
				value: value
			}
		})
	},
	//用户注册
	register(uname, upwd, rname, email, phone) {
		return request({
			url: '/auth/register',
			method: 'get',
			params: {
				uname: uname,
				upwd: upwd,
				rname: rname,
				email: email,
				phone: phone
			}
		})
	},

	get_Curr_Chart(param) {
		return request({
			url: '/auth/get_Curr_Chart',
			method: 'get',
			params: {
				param: param,
			}
		})
	},
	get_hist_Chart(param) {
		return request({
			url: '/auth/get_hist_Chart',
			method: 'get',
			params: {
				param: param,
			}
		})
	},

	get_limit() {
		return request({
			url: '/auth/get_limit',
			method: 'get',
			params: {}
		})
	},
	set_limit(wdL, sdL, kqzlL) {
		return request({
			url: '/auth/set_limit',
			method: 'get',
			params: {
				wdL: wdL,
				sdL: sdL,
				kqzlL: kqzlL,
			}
		})
	},
	scene_update(sid) {
		return request({
			url: '/auth/scene_update',
			method: 'get',
			params: {
				sid: sid,
			}
		})
	},
	get_face(baseImage) {
		return request({
			url: '/util/getFace',
			method: 'get',
			params: {
				baseImage: baseImage,
			}
		})
	},
	get_exe_data() {
		return request({
			url: '/auth/get_all_history',
			method: 'get',
			params: {}
		})
	},
	get_jwd() {
		return request({
			url: '/auth/get_jwd',
			method: 'get',
			params: {}
		})
	},
	set_jwd(jd,wd) {
		return request({
			url: '/auth/set_jwd',
			method: 'get',
			params: {
				jd: jd,
				wd: wd,
			}
		})
	},

}