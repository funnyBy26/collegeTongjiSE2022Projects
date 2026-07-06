<template>
  <div class="custom-loading">
    <div class="loading-spinner">
      <div class="circle"></div>
      <div class="circle"></div>
      <div class="circle"></div>
    </div>
    <div class="loading-text">加载中...</div>
  </div>
</template>

<style scoped>
.custom-loading {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 20px;
}

.loading-spinner {
  display: flex;
  gap: 8px;
}

.circle {
  width: 20px;
  height: 20px;
  border-radius: 50%;
  background-color: #409eff;
  animation: bounce 0.5s ease-in-out infinite;
}

.circle:nth-child(2) {
  animation-delay: 0.1s;
}

.circle:nth-child(3) {
  animation-delay: 0.2s;
}

.loading-text {
  color: #409eff;
  font-size: 18px;
  font-weight: bold;
}

@keyframes bounce {
  0%, 100% {
    transform: translateY(0);
  }
  50% {
    transform: translateY(-15px);
  }
}
</style> 