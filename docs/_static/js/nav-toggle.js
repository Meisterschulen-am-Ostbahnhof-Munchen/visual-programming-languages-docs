// nav-toggle.js — Global navigation collapse/expand toggle for MkDocs Material
(function () {
  'use strict';

  const STORAGE_KEY = 'nav-toggle-collapsed';
  const ICON_EXPAND = 'material/unfold-more';
  const ICON_COLLAPSE = 'material/unfold-less';
  const LABEL_EXPAND = 'Alle ausklappen';
  const LABEL_COLLAPSE = 'Alle einklappen';

  function isCollapsed() {
    return document.body.getAttribute('data-nav-collapsed') === 'true';
  }

  function setCollapsed(collapsed) {
    document.body.setAttribute('data-nav-collapsed', String(collapsed));
    sessionStorage.setItem(STORAGE_KEY, String(collapsed));
    updateButton();
  }

  function toggleNav() {
    const collapsed = !isCollapsed();
    const navItems = document.querySelectorAll('.md-nav__item--nested');

    navItems.forEach(function (item) {
      const toggle = item.querySelector('.md-toggle');
      const list = item.querySelector('.md-nav__list');
      if (toggle) {
        toggle.checked = !collapsed;
      }
      if (list) {
        list.style.display = collapsed ? 'none' : '';
      }
    });

    setCollapsed(collapsed);
  }

  function updateButton() {
    const btn = document.getElementById('nav-toggle-btn');
    if (!btn) return;
    const collapsed = isCollapsed();
    const icon = btn.querySelector('.md-icon');
    const label = btn.querySelector('.nav-toggle-label');

    if (icon) {
      icon.textContent = collapsed ? ':' + ICON_EXPAND + ':' : ':' + ICON_COLLAPSE + ':';
    }
    if (label) {
      label.textContent = collapsed ? LABEL_EXPAND : LABEL_COLLAPSE;
    }
  }

  function createButton() {
    const sidebar = document.querySelector('.md-sidebar--primary .md-sidebar__inner');
    if (!sidebar) return;

    const btn = document.createElement('button');
    btn.id = 'nav-toggle-btn';
    btn.className = 'md-button nav-toggle-btn';
    btn.type = 'button';
    btn.innerHTML =
      '<span class="md-icon">:' + ICON_COLLAPSE + ':</span>' +
      '<span class="nav-toggle-label">' + LABEL_COLLAPSE + '</span>';
    btn.addEventListener('click', toggleNav);

    sidebar.insertBefore(btn, sidebar.firstChild);
  }

  function init() {
    const stored = sessionStorage.getItem(STORAGE_KEY);
    const collapsed = stored === 'true';
    document.body.setAttribute('data-nav-collapsed', String(collapsed));
    createButton();
    if (collapsed) {
      // Apply collapsed state without toggling storage again
      const navItems = document.querySelectorAll('.md-nav__item--nested');
      navItems.forEach(function (item) {
        const toggle = item.querySelector('.md-toggle');
        const list = item.querySelector('.md-nav__list');
        if (toggle) toggle.checked = false;
        if (list) list.style.display = 'none';
      });
      updateButton();
    }
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }
})();
