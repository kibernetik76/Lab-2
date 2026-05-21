import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

df = pd.read_csv('results.csv')

# ================================================================
# ГРАФИК 1 — Общее сравнение времени поиска
# ================================================================
fig, ax = plt.subplots(figsize=(10, 6))
fig.suptitle('Сравнение всех алгоритмов поиска', fontsize=14, fontweight='bold')

colors  = ['#e74c3c', '#3498db', '#9b59b6', '#27ae60', '#e67e22']
markers = ['o', 's', '^', 'D', 'x']
labels  = ['Линейный', 'BST', 'Красно-чёрное дерево', 'Хэш-таблица', 'std::multimap']
cols    = ['Linear_us', 'BST_us', 'RBT_us', 'Hash_us', 'Multimap_us']

for col, label, color, marker in zip(cols, labels, colors, markers):
    ax.plot(df['Size'], df[col], marker=marker, color=color, linewidth=2, markersize=6, label=label)

ax.set_xlabel('Размер массива', fontsize=11)
ax.set_ylabel('Время (мкс)', fontsize=11)
ax.legend(fontsize=10)
ax.grid(True, alpha=0.3)
ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda x,_: f'{int(x):,}'.replace(',', ' ')))

plt.tight_layout()
plt.savefig('search_benchmark.png', dpi=150, bbox_inches='tight')
plt.close()

# ================================================================
# ГРАФИК 2 — Коллизии
# ================================================================
fig2, ax3 = plt.subplots(figsize=(9, 5))

ax3.plot(df['Size'], df['Collisions'], 'o-', color='#e74c3c', linewidth=2.5, markersize=7, label='Коллизии')

ax3.set_xlabel('Размер массива', fontsize=11)
ax3.set_ylabel('Число коллизий', fontsize=11)
ax3.set_title('Зависимость числа коллизий от размера массива', fontsize=12)
ax3.legend(fontsize=10)
ax3.grid(True, alpha=0.3)
ax3.xaxis.set_major_formatter(ticker.FuncFormatter(lambda x,_: f'{int(x):,}'.replace(',', ' ')))
ax3.yaxis.set_major_formatter(ticker.FuncFormatter(lambda y,_: f'{int(y):,}'.replace(',', ' ')))

plt.tight_layout()
plt.savefig('collisions.png', dpi=150, bbox_inches='tight')
plt.close()

# ================================================================
# ГРАФИК 3 — Детальное сравнение (без Linear)
# ================================================================
fig3, ax4 = plt.subplots(figsize=(10, 5))

fast_cols   = ['BST_us', 'RBT_us', 'Hash_us', 'Multimap_us']
fast_labels = ['BST', 'Красно-чёрное дерево', 'Хэш-таблица', 'std::multimap']
fast_colors = ['#3498db', '#9b59b6', '#27ae60', '#e67e22']
fast_marks  = ['s', '^', 'D', 'x']

for col, label, color, marker in zip(fast_cols, fast_labels, fast_colors, fast_marks):
    ax4.plot(df['Size'], df[col], marker=marker, color=color, linewidth=2, markersize=7, label=label)

ax4.set_xlabel('Размер массива', fontsize=11)
ax4.set_ylabel('Время (мкс)', fontsize=11)
ax4.set_title('Сравнение нелинейных методов поиска', fontsize=12)
ax4.legend(fontsize=10)
ax4.grid(True, alpha=0.3)
ax4.xaxis.set_major_formatter(ticker.FuncFormatter(lambda x,_: f'{int(x):,}'.replace(',', ' ')))

plt.tight_layout()
plt.savefig('search_fast.png', dpi=150, bbox_inches='tight')
plt.close()