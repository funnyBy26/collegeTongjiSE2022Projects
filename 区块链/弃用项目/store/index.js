import { createStore } from "vuex";
import ipfsStore from "./ipfs";

export default createStore({
  state: {},
  getters: {},
  mutations: {},
  actions: {},
  modules: {
    ipfs: ipfsStore,
  },
});
