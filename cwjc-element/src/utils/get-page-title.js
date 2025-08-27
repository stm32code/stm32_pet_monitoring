import defaultSettings from '@/settings'

const title = defaultSettings.title || '我的系统'

export default function getPageTitle(pageTitle) {
  if (pageTitle) {
    return `${pageTitle} - ${title}`
  }
  return `${title}`
}
