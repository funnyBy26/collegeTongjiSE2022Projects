<template>
  <div class="global-container">
    <div v-if="loadingStore.isLoading" class="loading-container">
      <LoadingComponent />
    </div>
    <div :class="{ 'content-hidden': loadingStore.isLoading, 'content-visible': !loadingStore.isLoading }">
      <slot></slot>
    </div>
  </div>
</template>

<script setup>
import { useLoadingStore } from '@/stores/loadingStore'
import LoadingComponent from './LoadingComponent.vue'

const loadingStore = useLoadingStore()
</script>

<style scoped>
.global-container {
  width: 100%;
  height: 100%;
}

.loading-container {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  background-color: #f5f7fa;
  z-index: 9999;
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
</style> 