// nav-toggle.js — Global navigation collapse/expand toggle for MkDocs Material
(function () {
  'use strict';

  const SVG_EXPAND = '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" width="20" height="20" fill="currentColor"><path d="M12 18.17L8.83 15l-1.41 1.41L12 21l4.59-4.59L15.17 15M12 5.83L15.17 9l1.41-1.41L12 3 7.41 7.41 8.83 9 12 5.83z"/></svg>';
  const SVG_COLLAPSE = '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" width="20" height="20" fill="currentColor"><path d="M12 8L16.59 12.59 18 11.17 12 5.17 6 11.17 7.41 12.59 12 8zm0 8l-4.59-4.59L6 12.83l6 6 6-6-1.41-1.42L12 16z"/></svg>';
  const LABEL_EXPAND = 'Alle ausklappen';
  const LABEL_COLLAPSE = 'Alle einklappen';

  function isCollapsed() {
    return document.body.getAttribute('data-nav-collapsed') === 'true';
  }

  function setCollapsed(collapsed) {
    document.body.setAttribute('data-nav-collapsed', String(collapsed));
    updateWidget();
  }

  function toggleNav() {
    const collapsed = !isCollapsed();

    const toggles = document.querySelectorAll('.md-sidebar--primary .md-toggle');
    toggles.forEach(function (toggle) {
      toggle.checked = !collapsed;
    });

    const subLists = document.querySelectorAll(
      '.md-sidebar--primary .md-nav__item--section > .md-nav > .md-nav__list > .md-nav__item--nested > .md-nav > .md-nav__list'
    );
    subLists.forEach(function (list) {
      list.style.display = collapsed ? 'none' : '';
    });

    setCollapsed(collapsed);
  }

  function updateWidget() {
    const btn = document.getElementById('nav-toggle-btn');
    const label = document.getElementById('nav-toggle-label');
    if (!btn || !label) return;
    const collapsed = isCollapsed();

    btn.querySelector('.md-icon').innerHTML = collapsed ? SVG_EXPAND : SVG_COLLAPSE;
    label.textContent = collapsed ? LABEL_EXPAND : LABEL_COLLAPSE;
    btn.setAttribute('aria-pressed', String(!collapsed));
    btn.setAttribute('aria-expanded', String(!collapsed));
  }

  function createWidget() {
    const sidebar = document.querySelector('.md-sidebar--primary .md-sidebar__inner');
    if (!sidebar) return;

    const wrapper = document.createElement('div');
    wrapper.className = 'nav-toggle-wrapper';

    const btn = document.createElement('button');
    btn.id = 'nav-toggle-btn';
    btn.className = 'md-button nav-toggle-btn';
    btn.type = 'button';
    btn.setAttribute('aria-label', LABEL_COLLAPSE);
    btn.setAttribute('aria-pressed', String(true));
    btn.setAttribute('aria-expanded', String(true));
    btn.innerHTML = '<span class="md-icon">' + SVG_COLLAPSE + '</span>';
    btn.addEventListener('click', toggleNav);

    const label = document.createElement('span');
    label.id = 'nav-toggle-label';
    label.className = 'nav-toggle-label';
    label.textContent = LABEL_COLLAPSE;

    wrapper.appendChild(btn);
    wrapper.appendChild(label);
    sidebar.insertBefore(wrapper, sidebar.firstChild);
  }

  function init() {
    document.body.setAttribute('data-nav-collapsed', 'false');
    createWidget();
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }
})();
