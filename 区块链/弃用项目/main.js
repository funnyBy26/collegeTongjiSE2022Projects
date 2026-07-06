import { createApp } from "vue";
import { createPinia } from 'pinia'
import App from "./App.vue";
import router from "./router";
import store from "./store";
// 引入Element Plus
import ElementPlus from 'element-plus'
// 引入Element Plus样式
import 'element-plus/dist/index.css'
// 如果需要使用中文，还需要引入中文语言包
import zhCn from 'element-plus/dist/locale/zh-cn.mjs'

const app = createApp(App)
app.use(createPinia())
app.use(store).use(router).use(ElementPlus, { locale: zhCn }).mount("#app");
