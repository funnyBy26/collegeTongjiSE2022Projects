<template>
  <div class="menu-bar-container">
    <MenuBar />
  </div>

  <div class="appointment-page">
    <!-- 日期选择器 -->
    <div class="date-selector">
      <div class="selector-container">
        <el-button 
          class="back-button" 
          @click="goBack"
          type="primary"
          :icon="ArrowLeft"
        >
          返回主页
        </el-button>
        <span class="date-label">请选择预约挂号的日期：</span>
        <el-date-picker
          v-model="selectedDate"
          type="date"
          :disabled-date="disabledDate"
          placeholder="请选择预约日期"
          format="YYYY-MM-DD"
          value-format="YYYY-MM-DD"
          @change="handleDateChange"
        />
      </div>
    </div>

    <!-- 医生列表 -->
    <div class="doctor-list">
      <div v-if="!selectedDate" class="empty-state">
        <el-empty description="请先选择预约挂号时间" />
      </div>
      <div v-else  class="empty-state">
        <el-collapse v-model="activeDoctor" class="doctor-collapse">
        <el-collapse-item
          v-for="doctor in filteredDoctors"
          :key="doctor.id"
          :name="doctor.id"
          class="doctor-item"
        >
          <template #title>
            <div class="doctor-info">
              <div class="left-section">
                <img 
                  :src="doctor.avatar" 
                  class="doctor-avatar"
                />
                <div class="doctor-details">
                  <div class="name-title">
                    <h3 class="doctor-name">{{ doctor.name }}</h3>
                    <span class="position">{{ doctor.position }}</span>
                  </div>
                  <div class="hospital">第一人民医院</div>
                  <div class="specialties">擅长：{{ doctor.specialties }}</div>
                </div>
              </div>
              <div class="action-button">
                点击显示可预约时间：
              </div>
            </div>
          </template>

          <!-- 时间段选择 -->
          <div class="time-slots">
            <div v-for="slot in doctor.timeSlots" :key="slot.time" class="time-slot">
              <span>{{ slot.time }}</span>
              <el-button
                :type="slot.available ? 'primary' : 'info'"
                :disabled="!slot.available"
                size="small"
                @click="handleAppointment(doctor, slot)"
              >
                {{ slot.available ? `剩余${slot.count}号` : '已约满' }}
              </el-button>
            </div>
          </div>
        </el-collapse-item>
      </el-collapse>
      </div>
    </div>

    <!-- 添加预约弹窗 -->
    <AppointmentDialog
      v-model:visible="dialogVisible"
      :doctor-info="selectedDoctor"
      :appointment-info="selectedAppointment"
      :user-info="userInfo"
      @submit="handleSubmitAppointment"
    />

    <!-- 添加结果提示弹窗 -->
    <ResultDialog
      v-model:visible="resultDialogVisible"
      :is-success="appointmentSuccess"
    />
  </div>
</template>

<script setup>
import { ref, computed, nextTick } from 'vue'
import { useRouter } from 'vue-router'
import { ArrowLeft } from '@element-plus/icons-vue'
import dayjs from 'dayjs'
import MenuBar from '@/components/MenuBar.vue' 
import AppointmentDialog from '@/components/AppointmentDialog.vue'
import ResultDialog from '@/components/ResultDialog.vue'

const router = useRouter()

// 选中的日期
const selectedDate = ref('')
// 当前开的医生ID
const activeDoctor = ref('')

// 禁用日期（只能选择今天及未来7天）
const disabledDate = (time) => {
  const today = dayjs().startOf('day')
  const maxDate = today.add(7, 'day')
  return time.getTime() < today.valueOf() || time.getTime() > maxDate.valueOf()
}

// 模拟医生数据
const doctors = ref([
  {
    id: 1,
    name: '张医生',
    position: '主任医师',
    avatar: 'path/to/avatar',
    hospital: '第一人民医院',
    specialties: '心脏内科、高血压',
    hasAvailableSlots: true,
    timeSlots: [
      { time: '09:00-10:00', available: true, count: 5 },
      { time: '10:00-11:00', available: false, count: 0 },
      { time: '11:00-12:00', available: true, count: 3 },
      // ... 更多时间段
    ]
  },
  {
    id: 2,
    name: '文医生',
    position: '院长',
    avatar: 'https://example.com/avatar2.jpg',
    hospital: '笑容诊所',
    specialties: '牙齿矫正、牙齿美白',
    hasAvailableSlots: true,
    timeSlots: [
      { time: '09:00-10:00', available: true, count: 7 },
      { time: '10:00-11:00', available: false, count: 0 },
      { time: '11:00-12:00', available: true, count: 6 },
      { time: '12:00-13:00', available: true, count: 6 },
      { time: '13:00-14:00', available: true, count: 6 },
      { time: '14:00-15:00', available: true, count: 6 },
      { time: '15:00-16:00', available: true, count: 6 },
      { time: '16:00-17:00', available: true, count: 6 },
      { time: '17:00-18:00', available: true, count: 6 },
      { time: '18:00-19:00', available: true, count: 6 },
      { time: '19:00-20:00', available: true, count: 6 },
      // ... 更多时间段
    ]
  },
  // ... 更多医生
])

// 根据日期筛选医生
const filteredDoctors = computed(() => {
  if (!selectedDate.value) return []
  return doctors.value
})

// 处理日期变化
const handleDateChange = (date) => {
  // 这里可以调用API获取对应日期的医生排班信息
  console.log('选择的日期：', date)
}

// 处理预约
const handleAppointment = (doctor, slot) => {
  if (!slot.available) return
  
  selectedDoctor.value = {
    ...doctor,
    location: '门诊楼5层503诊室',
    introduction: '从事心血管疾病临床诊治工作20余年，具有丰富的临床经验。擅长高血压、冠心病、心力衰竭等常见心血管疾病的诊治。'
  }
  selectedAppointment.value = {
    date: selectedDate.value,
    timeSlot: slot.time
  }
  
  // 确保所有数据都准备好后再显示对话框
  nextTick(() => {
    dialogVisible.value = true
  })
}


const goBack = () => {
  router.push('/')
}

const dialogVisible = ref(false)
const selectedDoctor = ref({})
const selectedAppointment = ref({})
const userInfo = ref({
  name: '张三',
  idCard: '110101199001011234'
})

const resultDialogVisible = ref(false)
const appointmentSuccess = ref(false)

const handleSubmitAppointment = async (data) => {
  try {
    // 调用后端 API
    const response = await fetch('/api/appointment', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(data)
    })
    
    const result = await response.json()
    
    // 关闭预约弹窗
    dialogVisible.value = false
    
    // 设置预约结果
    appointmentSuccess.value = result.success
    
    // 显示结果弹窗
    resultDialogVisible.value = true
    
  } catch (error) {
    console.error('预约失败:', error)
    appointmentSuccess.value = false
    resultDialogVisible.value = true
  }
}
</script>

<style scoped>
.menu-bar-container{
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  z-index: 1000;
}
.appointment-page {
  max-width: 1200px;
  margin: 120px auto 0;
  padding: 20px;
}

.date-selector {
  margin-bottom: 30px;
  padding: 20px;
  background-color: #f5f7fa;
  border-radius: 8px;
}

.selector-container {
  display: flex;
  align-items: center;
  gap: 20px;
}

.back-button {
  padding: 8px 16px;
  font-size: 14px;
}

.date-label {
  font-weight: bold;
  font-size: 16px;
  color: #333;
}
.doctor-item {
  border: 1px solid #e4e7ed;
  border-radius: 20px;
  margin-bottom: 10px;
}
.doctor-list {
  margin-top: 30px;
}
.empty-state {
  padding: 40px;
  background-color: #f5f7fa;
  border-radius: 8px;
  text-align: center;
}
.doctor-info {
  display: flex;
  justify-content: space-between;
  align-items: center;
  width: 100%;
  padding: 15px 20px;
  box-sizing: border-box;
}

.left-section {
  display: flex;
  gap: 20px;
  align-items: flex-start;
}

.doctor-details {
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  height: 100px;
  gap: 6px;
  padding: 8px 0;
}

.name-title {
  display: flex;
  align-items: center;
  gap: 12px;
  width: 100%;
}

.doctor-name {
  margin: 0;
  font-size: 18px;
  font-weight: bold;
  color: #333;
  line-height: 1.2;
}

.position {
  font-size: 18px;
  color: #666;
  line-height: 1.2;
}

.hospital {
  margin-top: 8px;
  padding: 0;
  font-size: 16px;
  color: #666;
  line-height: 1.2;
}

.specialties {
  margin-top: 8px;
  padding: 0;
  font-size: 16px;
  color: #666;
  line-height: 1.2;
}

.action-button {
  margin-left: auto;
  flex-shrink: 0;
}

.action-button :deep(.el-button) {
  width: 140px;
  white-space: nowrap;
}

.time-slots {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
  gap: 20px;
  padding: 20px;
}

.time-slot-card {
  margin-bottom: 15px;
}

.time-slot {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 10px;
}

.time-slot span {
  font-size: 14px;
  color: #333;
}

/* 手风琴面板样式 */
:deep(.el-collapse-item__wrap) {
  border: 1px solid #e4e7ed;
  border-radius: 8px;
  margin-bottom: 10px;
  background-color: #fff;
  overflow: hidden;
}

:deep(.el-collapse-item__header) {
  padding: 0;
  height: auto;
  background-color: #fff;
  border: none;
  border-radius: 8px;
}

:deep(.el-collapse-item__content) {
  padding: 20px;
  background-color: #fff;
}

:deep(.el-collapse-item.is-active .el-collapse-item__header) {
  border-bottom-left-radius: 0;
  border-bottom-right-radius: 0;
}
.doctor-collapse {
  border-radius: 20px;
}
.doctor-avatar {
  width: 100px;
  height: 100px;
  object-fit: cover;
}

</style> 