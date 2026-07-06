<template>
  <el-dialog
    v-model="isVisible"
    :title="isSuccess ? '预约成功' : '预约失败'"
    width="30%"
    :show-close="isSuccess"
    :close-on-click-modal="isSuccess"
    :close-on-press-escape="isSuccess"
  >
    <div class="result-content">
      <div :class="['status-icon', isSuccess ? 'success' : 'error']">
        <el-icon v-if="isSuccess">
          <CircleCheckFilled />
        </el-icon>
        <el-icon v-else>
          <CircleCloseFilled />
        </el-icon>
      </div>
      
      <div v-if="isSuccess" class="message">
        您已预约成功，可进入个人中心查看预约详细信息
      </div>
      
      <div v-else class="message">
        <div>很抱歉，您的预约失败</div>
        <div class="countdown">{{ countdown }}秒后将跳转到主页，您可以重新进行预约挂号</div>
      </div>
    </div>

    <template #footer>
      <div class="dialog-footer">
        <el-button v-if="isSuccess" @click="handleClose">确定</el-button>
        <el-button v-else type="primary" @click="goToHome">立即跳转</el-button>
      </div>
    </template>
  </el-dialog>
</template>

<script setup>
import { ref, defineProps, defineEmits, watch } from 'vue'
import { useRouter } from 'vue-router'
import { CircleCheckFilled, CircleCloseFilled } from '@element-plus/icons-vue'

const props = defineProps({
  visible: Boolean,
  isSuccess: Boolean
})

const emit = defineEmits(['update:visible'])
const router = useRouter()
const countdown = ref(5)
const isVisible = ref(props.visible)

// 监听visible变化
watch(() => props.visible, (newVal) => {
  isVisible.value = newVal
  if (newVal && !props.isSuccess) {
    startCountdown()
  }
})

// 监听isVisible变化
watch(isVisible, (newVal) => {
  emit('update:visible', newVal)
})

const startCountdown = () => {
  countdown.value = 5
  const timer = setInterval(() => {
    countdown.value--
    if (countdown.value <= 0) {
      clearInterval(timer)
      goToHome()
    }
  }, 1000)
}

const handleClose = () => {
  isVisible.value = false
}

const goToHome = () => {
  router.push('/')
}
</script>

<style scoped>
.result-content {
  display: flex;
  flex-direction: column;
  align-items: center;
  padding: 20px 0;
}

.status-icon {
  font-size: 48px;
  margin-bottom: 20px;
}

.status-icon :deep(.el-icon) {
  font-size: inherit;
}

.success {
  color: #67C23A;
}

.error {
  color: #F56C6C;
}

.message {
  text-align: center;
  font-size: 16px;
  line-height: 1.5;
}

.countdown {
  margin-top: 10px;
  color: #666;
}

.dialog-footer {
  display: flex;
  justify-content: center;
}
</style> 