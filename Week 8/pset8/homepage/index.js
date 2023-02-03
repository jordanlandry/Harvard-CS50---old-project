const likes = [];

const addLike = () => {
  const el = document.getElementById("like-input");
  const userLikes = document.getElementById("user-likes");
  const newItem = document.createElement("li");

  if (likes.length >= 5) {
    alert("Maximum number of 5 items exceeded");
    return;
  }

  if (likes.includes(el.value.toLowerCase())) {
    alert("Please input a unique item");
    return;
  }

  if (el.value === "") {
    alert("Please do not leave this field empty");
    return;
  }

  likes.push(el.value.toLowerCase());
  newItem.appendChild(document.createTextNode(el.value));
  userLikes.appendChild(newItem);
};
