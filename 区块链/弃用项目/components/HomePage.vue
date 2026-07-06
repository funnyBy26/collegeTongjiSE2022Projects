<template>
  <div class="hello">
    <!-- Loading 状态 -->
    <div v-if="loadingStore.isLoading" class="loading-container">
      <el-loading-component />
    </div>

    <!-- 所有内容包裹在一个容器中，根据加载状态显示/隐藏 -->
    <div :class="{ 'content-hidden': loadingStore.isLoading, 'content-visible': !loadingStore.isLoading }">
      <MenuBar />
      
      <video 
        ref="videoRef"
        autoplay 
        loop 
        muted 
        class="background-video"
        @canplay="handleVideoReady"
        preload="auto"
      >
        <source src="@/assets/welcome.mp4" type="video/mp4">
      </video>

      <div class="button-container">
        <el-button 
          type="primary" 
          size="large" 
          class="action-button" 
          @click="goToRegister"
        >
          前往挂号
        </el-button>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import MenuBar from './MenuBar.vue'
import { useLoadingStore } from '@/stores/loadingStore'

const router = useRouter()
const loadingStore = useLoadingStore()
const videoRef = ref(null)

const handleVideoReady = () => {
  loadingStore.setLoading(false)
}

const goToRegister = () => {
  router.push('/register')
}

// 在组件挂载时开始加载视频
onMounted(() => {
  loadingStore.setLoading(true)
  if (videoRef.value && videoRef.value.readyState >= 3) {
    loadingStore.setLoading(false)
  }
})
</script>

<style scoped>
.hello {
  position: relative;
  width: 100%;
  height: 100vh;
}

.loading-container {
  position: fixed;  /* 改为 fixed 确保全屏覆盖 */
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  background-color: #f5f7fa;
  z-index: 9999;  /* 确保在最上层 */
}

.content-hidden {
  opacity: 0;
  visibility: hidden;
  transition: opacity 0.3s ease, visibility 0.3s ease;
}

.content-visible {
  opacity: 1;
  visibility: visible;
  transition: opacity 0.3s ease, visibility 0.3s ease;
}

.background-video {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  object-fit: cover;
  z-index: -1;
}

.button-container {
  position: absolute;
  top: 42%;
  right: 6%;  
  transform: translate(0, -50%);
  z-index: 1;
}

.action-button {
  font-size: 36px;
  padding: 45px 60px;
  border-radius: 20px;
  font-weight: bold;
}
</style>
