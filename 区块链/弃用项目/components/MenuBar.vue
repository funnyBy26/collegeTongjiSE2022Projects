<template>
  <div class="header-container">
    <!-- 左侧 Logo 和应用名称 -->
    <div class="left-section">
      <el-image
        class="logo"
        :src="logoUrl"
        fit="cover"
      />
    </div>

    <!-- 右侧用户信息 -->
    <div class="right-section">
      <el-dropdown   size="large">
        <template #dropdown>
            <el-dropdown-menu>
              <el-dropdown-item @click="handlePersonalCenter">个人中心</el-dropdown-item>
              <el-dropdown-item @click="handleSettings">设置</el-dropdown-item>
              <el-dropdown-item divided @click="handleLogout">退出登录</el-dropdown-item>
            </el-dropdown-menu>
          </template>
          <span class="avatar-container">
            <el-avatar
              :size="96"
              :src="userInfo.avatar"
            />
            <el-icon class="el-icon--right">
              <arrow-down />
            </el-icon>
          </span>
          
        </el-dropdown>
      <el-space :size="20">
        <!-- 用户基本信息 -->
        <div class="user-info">
          <div class="info-row">
            <el-text class="info-item">
              <span class="label">姓名：</span>
              {{ userInfo.name }}
            </el-text>
          </div>
          <div class="info-row">
            <el-text class="info-item">
              <span class="label">手机：</span>
              {{ formatPhone(userInfo.phone) }}
            </el-text>
          </div>
          <div class="info-row">
            <el-text class="info-item">
              <span class="label">ID号：</span>
              {{ formatIdCard(userInfo.idCard) }}
            </el-text>
          </div>
        </div>
        
        
      </el-space>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import { ArrowDown } from '@element-plus/icons-vue'
import logoImage from '@/assets/logo.png'

// 定义 props 或使用状态管理存储的数据
const logoUrl = logoImage


const userInfo = ref({
  name: '张三',
  idCard: '310000199001011234',
  phone: '13800138000',
  avatar: 'https://example.com/avatar.jpg'
})

// 格式化身份证号，中间部分用 * 代替
const formatIdCard = (idCard) => {
  if (!idCard) return ''
  return idCard.replace(/^(.{6})(?:\d+)(.{4})$/, '$1********$2')
}

// 格式化手机号，中间部分用 * 代替
const formatPhone = (phone) => {
  if (!phone) return ''
  return phone.replace(/^(\d{3})\d{4}(\d{4})$/, '$1****$2')
}

// 处理点击事件
const handlePersonalCenter = () => {
  // 处理个人中心点击
}

const handleSettings = () => {
  // 处理设置点击
}

const handleLogout = () => {
  // 处理退出登录
}
</script>

<style scoped>
.header-container {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0 20px;
  height: 120px;
  background-color: rgb(94, 148, 254);
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}

.left-section {
  display: flex;
  align-items: center;
}

.logo {
  width: 96px;
  height: 96px;
  margin-right: 12px;
  border-radius: 50%;
  overflow: hidden;
}

.app-name {
  font-size: 16px;
  font-weight: normal;
  color: #FFFFFF;
  margin: 0;
}

.right-section {
  display: flex;
  align-items: center;
}

.user-info {
  display: flex;
  flex-direction: column;
  gap: 8px;
}

.info-row {
  display: flex;
}

.info-item {
  font-size: 16px;
  color: #FFFFFF;
}

.label {
  color: #FFFFFF;
}

.el-dropdown {
  outline: none !important;
}

.avatar-container {
  display: flex;
  align-items: center;
  cursor: pointer;
}

.el-icon--right {
  margin-left: 8px;
  color: #FFFFFF;
}
</style>