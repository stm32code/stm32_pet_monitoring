import Vue from 'vue'

import 'normalize.css/normalize.css' // A modern alternative to CSS resets

import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'
import locale from 'element-ui/lib/locale/lang/en' // lang i18n

import '@/styles/index.scss' // global css

import App from './App'
import store from './store'
import router from './router'

import '@/icons' // icon
import '@/permission' // permission control
import VueClipboard from 'vue-clipboard2'
import dataV from '@jiaminghi/data-view'
import JsonExcel from 'vue-json-excel'
import BaiduMap from 'vue-baidu-map'
// 百度地图
Vue.use(BaiduMap, {
  // ak 是在百度地图开发者平台申请的密钥
  ak: 'afCVFoKCbzUSXV5xyXZIwy0KpWb1zRGH'
})

// import dataV from '@jiaminghi/data-view'

/**
 * If you don't want to use mock-server
 * you want to use MockJs for mock api
 * you can execute: mockXHR()
 *
 * Currently MockJs will be used in the production environment,
 * please remove it before going online ! ! !
 */
if (process.env.NODE_ENV === 'production') {
  const { mockXHR } = require('../mock')
  mockXHR()
}

// set ElementUI lang to EN
Vue.use(ElementUI, { locale })
Vue.use(VueClipboard)
Vue.use(dataV)
Vue.component('downloadExcel', JsonExcel)
// 如果想要中文版 element-ui，按如下方式声明
// Vue.use(ElementUI)

Vue.config.productionTip = false

new Vue({
  el: '#app',
  router,
  store,
  render: h => h(App)
})
