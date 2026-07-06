<template>
  <el-dialog
    v-if="doctorInfo && appointmentInfo"
    v-model="isVisible"
    title="预约挂号"
    width="60%"
    :before-close="handleClose"
    destroy-on-close
  >
    <!-- 医生信息卡片 -->
    <el-card class="doctor-card">
      <div class="doctor-info">
        <img :src="doctorInfo.avatar" class="doctor-avatar" />
        <div class="doctor-details">
          <div class="name-title">
            <h3>{{ doctorInfo?.name }}</h3>
            <span class="position">{{ doctorInfo?.position }}</span>
          </div>
          <div class="hospital">{{ doctorInfo?.hospital }}</div>
          <div class="specialties">擅长：{{ doctorInfo?.specialties }}</div>
          <div class="introduction">{{ doctorInfo?.introduction }}</div>
        </div>
      </div>
    </el-card>

    <!-- 修改预约信息表单 -->
    <el-form
      ref="formRef"
      :model="appointmentForm"
      label-width="120px"
      class="appointment-form"
    >
      <el-form-item>
        <template #label>
          <div class="label-container">
            <span>姓</span>
            <span>名</span>
          </div>
        </template>
        <span>{{ userInfo?.name }}</span>
      </el-form-item>

      <el-form-item label="身份证号">
        <span>{{ userInfo?.idCard }}</span>
      </el-form-item>

      <el-form-item label="预约时间">
        <span>{{ appointmentInfo?.date }} {{ appointmentInfo?.timeSlot }}</span>
      </el-form-item>

      <el-form-item label="就诊地点">
        <span>{{ doctorInfo?.location }}</span>
      </el-form-item>

      <el-form-item label="共享病历">
        <div class="records-container">
          <el-checkbox 
            v-for="record in medicalRecords" 
            :key="record.id" 
            :label="record.id"
            class="record-item"
          >
            {{ record.date }} - {{ record.description }}
          </el-checkbox>
        </div>
      </el-form-item>
    </el-form>

    <!-- 操作按钮 -->
    <template #footer>
      <div class="dialog-footer">
        <el-button @click="handleClose">取消</el-button>
        <el-button type="primary" @click="handleSubmit">
          确认信息并挂号
        </el-button>
      </div>
    </template>
  </el-dialog>
</template>

<script setup>
import { ref, defineProps, defineEmits, computed } from 'vue'

const props = defineProps({
  visible: {
    type: Boolean,
    default: false
  },
  doctorInfo: {
    type: Object,
    default: () => ({})
  },
  appointmentInfo: {
    type: Object,
    default: () => ({})
  },
  userInfo: {
    type: Object,
    default: () => ({
      name: '',
      idCard: ''
    })
  }
})

const emit = defineEmits(['update:visible', 'submit'])

// 使用计算属性来处理 dialog 的显示状态
const isVisible = computed({
  get: () => props.visible,
  set: (value) => emit('update:visible', value)
})

const formRef = ref(null)

// 模拟病历数据
const medicalRecords = ref([
  { id: 1, date: '2024-01-15', description: '普通感冒门诊' },
  { id: 2, date: '2024-02-20', description: '年度体检报告' },
  { id: 3, date: '2024-03-10', description: '心脏检查报告' },
{ id: 4, date: '2024-04-10', description: '心脏检查报告' },
  { id: 5, date: '2024-05-10', description: '心脏检查报告' },
  { id: 6, date: '2024-06-10', description: '心脏检查报告' },
  { id: 7, date: '2024-07-10', description: '心脏检查报告' },
  { id: 8, date: '2024-08-10', description: '心脏检查报告' },
  { id: 9, date: '2024-09-10', description: '心脏检查报告' },
  { id: 10, date: '2024-10-10', description: '心脏检查报告' },
])

// 简化表单数据，只保留病历选择
const appointmentForm = ref({
  selectedRecords: []
})

// 提交表单
const handleSubmit = async () => {
  // 构造提交数据
  const submitData = {
    patientInfo: {
      name: props.userInfo.name,
      idCard: props.userInfo.idCard
    },
    appointmentInfo: {
      doctorId: props.doctorInfo.id,
      date: props.appointmentInfo.date,
      timeSlot: props.appointmentInfo.timeSlot
    },
    sharedRecords: appointmentForm.value.selectedRecords
  }
  
  emit('submit', submitData)
  handleClose()
}

const handleClose = () => {
  emit('update:visible', false)
}
</script>

<style scoped>
.doctor-card {
  margin-bottom: 20px;
}

.doctor-info {
  display: flex;
  gap: 20px;
}

.doctor-avatar {
  width: 120px;
  height: 120px;
  object-fit: cover;
}

.doctor-details {
  flex: 1;
  text-align: left;
}

.name-title {
  display: flex;
  align-items: center;
  gap: 12px;
  margin-bottom: 8px;
}

.name-title h3 {
  margin: 0;
  font-size: 18px;
}

.position {
  color: #000000;
  font-size: 16px;
}

.hospital {
  margin-bottom: 8px;
  color: #000000;
  text-align: left;
}

.specialties {
  margin-bottom: 8px;
  color: #000000;
  text-align: left;
}

.introduction {
  color: #000000;
  line-height: 1.5;
  text-align: left;
}

.appointment-form {
  margin-top: 20px;
  color: #000000;
  text-align: left;
}

.dialog-footer {
  display: flex;
  justify-content: flex-end;
  gap: 12px;
}

.label-container {
  display: flex;
  justify-content: space-between;
  width: 60px;  /* 调整宽度以适应"姓"和"名"两个字 */
  font-weight: bold;
  font-size: 16px;
}

.records-container {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 20px;
  align-items: start;
}

.record-item {
  margin-right: 0;
  white-space: nowrap;
}

:deep(.el-form-item__label) {
  font-weight: bold !important;
  font-size: 16px !important;
}

/* 确保每个 checkbox 都从左侧开始 */
:deep(.el-checkbox) {
  margin-left: 0 !important;
  width: 100%;
}

:deep(.el-checkbox__label) {
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

/* 调整表单项的间距 */
.el-form-item {
  margin-bottom: 20px;
}
</style> 