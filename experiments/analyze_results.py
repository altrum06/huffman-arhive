import matplotlib.pyplot as plt

# Данные из эксперимента
sizes = [1, 10, 50, 100, 500]
ratios = [-22, 45, 52, 56, 56]  # степени сжатия

plt.figure(figsize=(8, 5))
plt.plot(sizes, ratios, 'bo-', linewidth=2)
plt.xlabel('Размер файла (КБ)')
plt.ylabel('Степень сжатия (%)')
plt.title('Эффективность сжатия Хаффмана')
plt.grid(True)
plt.axhline(y=0, color='r', linestyle='--')

for x, y in zip(sizes, ratios):
    plt.annotate(f'{y}%', (x, y), xytext=(0, 10), textcoords='offset points')

plt.savefig('graph.png')
plt.show()
print("График сохранён")