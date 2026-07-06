import { create } from "ipfs-http-client";

// 初始化 IPFS 客户端
const ipfs = create("https://ipfs.infura.io:5001/api/v0");

export default {
  state: {
    file: null,
    fileCID: null,
    error: null,
  },
  mutations: {
    setFile(state, file) {
      state.file = file;
    },
    setFileCID(state, fileCID) {
      state.fileCID = fileCID;
    },
    setError(state, error) {
      state.error = error;
    },
  },
  actions: {
    // 处理文件选择
    handleFileChange({ commit }, file) {
      commit("setFile", file);
    },
    // 上传文件到 IPFS
    async uploadFile({ state, commit }) {
      try {
        if (!state.file) {
          throw new Error("No file selected");
        }
        const added = await ipfs.add(state.file);
        commit("setFileCID", added.path);
      } catch (error) {
        commit("setError", error.message);
      }
    },
    // 获取文件信息
    async fetchFile({ commit }, cid) {
      try {
        const stream = ipfs.cat(cid);
        let fileContent = "";
        for await (const chunk of stream) {
          fileContent += chunk.toString();
        }
        return fileContent;
      } catch (error) {
        commit("setError", error.message);
      }
    },
  },
  getters: {
    fileCID: (state) => state.fileCID,
    file: (state) => state.file,
    error: (state) => state.error,
  },
};
