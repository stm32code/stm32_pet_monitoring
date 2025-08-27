import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

/* Layout */
import Layout from '@/layout'


/**
 * Note: sub-menu only appear when route children.length >= 1
 * Detail see: https://panjiachen.github.io/vue-element-admin-site/guide/essentials/router-and-nav.html
 *
 * hidden: true                   if set true, item will not show in the sidebar(default is false)
 * alwaysShow: true               if set true, will always show the root menu
 *                                if not set alwaysShow, when item has more than one children route,
 *                                it will becomes nested mode, otherwise not show the root menu
 * redirect: noRedirect           if set noRedirect will no redirect in the breadcrumb
 * name:'router-name'             the name is used by <keep-alive> (must set!!!)
 * meta : {
    roles: ['admin','editor']    control the page roles (you can set multiple roles)
    title: 'title'               the name show in sidebar and breadcrumb (recommend set)
    icon: 'svg-name'/'el-icon-x' the icon show in the sidebar
    breadcrumb: false            if set false, the item will hidden in breadcrumb(default is true)
    activeMenu: '/example/list'  if set path, the sidebar will highlight the path you set
  }
 */

/**
 * constantRoutes
 * a base page that does not have permission requirements
 * all roles can be accessed
 */
export const constantRoutes = [{
		path: '/login',
		component: () => import('@/views/login/index'),
		hidden: true
	},

	{
		path: '/404',
		component: () => import('@/views/404'),
		hidden: true
	},

	{
		path: '/',
		component: Layout,
		redirect: '/my/user_curr_data',
		children: [
			//   {
			//   path: 'index',
			//   name: 'index',
			//   component: () => import('@/views/my/user_curr_data'),
			//   meta: {
			//     title: '首页',
			//     icon: 'el-icon-s-home'
			//   }
			// },
		]
	},

	// 404 page must be placed at the end !!!
	{
		path: '*',
		redirect: '/404',
		hidden: true
	}
]

export const asyncRoutes = [
	//  {
	//    path: '/my',
	//    component: Layout,
	//    redirect: '/my/admin_user',
	//    name: '',
	//    meta: { title: '管理员功能', icon: 'el-icon-user-solid' ,roles: ['man'] },
	//    children: [
	// 		{
	// 		  path: 'admin_user',
	// 		  name: 'admin_user',
	// 		  component: () => import('@/views/my/admin_user'),
	// 		  meta: { title: '用户管理', icon: 'table', roles: ['man'] }
	// 		},
	//      {
	//        path: 'admin_operation',
	//        name: 'admin_operation',
	//        component: () => import('@/views/my/admin_operation'),
	//        meta: { title: '操作记录查看', icon: 'table', roles: ['man'] }
	//      },
	// {
	//   path: 'admin_idea',
	//   name: 'admin_idea',
	//   component: () => import('@/views/my/admin_idea'),
	//   meta: { title: '客户意见查看', icon: 'table', roles: ['man'] }
	// },

	//    ]
	//  },
	{
		path: '/my',
		component: Layout,
		redirect: '/my/user_curr_data',
		name: '',
		meta: {
			title: '系统管理',
			icon: 'el-icon-user-solid',
			roles: ['pan']
		},
		children: [
			// {
			//   path: 'user_sen',
			//   name: 'user_sen',
			//   component: () => import('@/views/my/user_sen'),
			//   meta: { title: '场景管理', icon: 'table', roles: ['pan'] }
			// },
			

			{
				path: 'user_curr_data',
				name: 'user_curr_data',
				component: () => import('@/views/my/user_curr_data'),
				meta: {
					title: '实时数据查看',
					icon: 'table',
					roles: ['pan']
				}
			},


		]
	},

	// 404 page must be placed at the end !!!
	{
		path: '*',
		redirect: '/404',
		hidden: true
	}
]



const createRouter = () => new Router({
	// mode: 'history', // require service support
	scrollBehavior: () => ({
		y: 0
	}),
	routes: constantRoutes
})

const router = createRouter()

// Detail see: https://github.com/vuejs/vue-router/issues/1234#issuecomment-357941465
export function resetRouter() {
	const newRouter = createRouter()
	router.matcher = newRouter.matcher // reset router
}

export default router