import { createRouter, createWebHashHistory } from "vue-router";
import HomeView from "../views/HomeView.vue";
import AppointmentPage from "../views/AppointmentPage.vue";
import RegisterView from "../views/RegisterView.vue";
import { useLoadingStore } from '@/stores/loadingStore'

const routes = [
  {
    path: "/",
    name: "home",
    component: HomeView,
  },
  {
    path: "/register",
    name: "register",
    component: RegisterView,
  },
  {
    path: "/register/appointment",
    name: "appointment",
    component: AppointmentPage,
  },
];

const router = createRouter({
  history: createWebHashHistory(),
  routes,
});

router.beforeEach((to, from, next) => {
  const loadingStore = useLoadingStore()
  loadingStore.setLoading(true)
  next()
})

router.afterEach(() => {
  const loadingStore = useLoadingStore()
  // 给一个小延迟确保页面内容已经渲染
  setTimeout(() => {
    loadingStore.setLoading(false)
  }, 500)
})

export default router;
